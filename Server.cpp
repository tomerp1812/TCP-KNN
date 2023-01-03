//
// Created by Dansa on 31/12/2022.
//



#include "Server.h"

Server::Server(Database* dB, const string& port) {
    this->database = dB;
    this->port = stoi(port);
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
}

/**
 * This function gets the data sent from the client and returns a classification of the new vector
 * brokeBuffer[0] = vector
 * brokeBuffer[1] = distance
 * brokeBuffer[2] = k
 * @param brokeBuffer - an array storing the data received from the client
 * @return a string storing the classification
 */
string Server::getClassifiction(string* brokeBuffer) {
    //when the database is created it has a default of k=1
    database->setK(stoi(brokeBuffer[2]));

    //choose the distance algorithm
    char* disAlg = new char[brokeBuffer[1].length() + 1];
    brokeBuffer[1].copy(disAlg, brokeBuffer[1].length(), 0);
    disAlg[brokeBuffer[1].length()] = '\0';
    //checking which distance algorithm to use
    Distance *dis = chooseDis(disAlg);
    //checking the validation of the new distance object
    if (dis == nullptr){
        delete[] disAlg;
        return "invalid input";
    }
    delete[] disAlg;

    //return  a new classified vector
    return newVectorClassification(this->database, dis, brokeBuffer[0]);

}

/**
 * This function divide and extract relevant data from the client message and store it in an array
 * @param brokeBuffer - the array to store the divided data
 * @param buffer - the data
 * @return true if there were no problems with the client message and false otherwise
 */
bool Server::breakBuffer(char *buffer, string* brokeBuffer) {
    string input;
    int t = 0;
    while(buffer[t] != '\0'){
        input += buffer[t];
        t++;
    }
    input += '\0';

    // create first string - vector
    string vectorString;
    int i = 0;
    while ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == ' ' || buffer[i] == '-'
    || buffer[i] == '.' || buffer[i] == 'E') {
        vectorString += buffer[i];
        i++;
    }
    //check the validation of the vector
    if(!checkStr(vectorString)){
        return false;
    }
    brokeBuffer[0] = vectorString;

    //check the validation of the rest of the client data
    if(input.length() - brokeBuffer[0].length() < 5){
        return false;
    }

    // create second string - distance (a 3 letters word)
    string distanceString;
    for (int j = 0; j < 3; j++) {
        distanceString += buffer[i];
        i++;
    }
    brokeBuffer[1] = distanceString;
    i++;

    // create third string - k (a number)
    string kString;
    while (buffer[i] != '\0') {
        kString += buffer[i];
        i++;
    }
    //check the validation of the k
    if(!isPositiveInteger(kString)){
        return false;
    }
    brokeBuffer[2] = kString;
    return true;
}

/**
 * This function implements a TCP socket connection protocol between a client and a server.
 */
void Server::tcpSocket() {

    //checking creation succeed
    if (sock < 0) {
        perror("error creating sock");
    }

    //for sending a group of parameters and get them back we create a struct
    struct sockaddr_in sin;
    //nullify the struct
    memset(&sin, 0 , sizeof(sin));
    //initialize the struct fields
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    //bind server to the port and check succeed
    if(bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding sock");
    }

    //setting to let up to 5 clients waiting
    if (listen(sock, 5) < 0) {
        perror("error listening to a sock");
    }
while(true) {
    //accept an incoming Client connection
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting Client");
    }

    while (true) {
        //set a buffer to hold the incoming data
        char buffer[4096] = {0};
        string classification;
        int expected_data_len = sizeof(buffer);
        long read_bytes = recv(client_sock, buffer, expected_data_len, 0);
        if (read_bytes == 0) {
            break;
        } else if (read_bytes < 0) {
            perror("error in receiving data");
            continue;
        } else {
            //buffer stores the received data! (vector, distance, k)
        }
        // convert buffer into array of 3 strings and send it to getClassification
        auto *brokeBuffer = new string[3];
        //check if the client wants to close the connection
        if(brokeBuffer[0] == "-1" && brokeBuffer->length() == 2){
            break;
        }
        if(breakBuffer(buffer, brokeBuffer)){
            //getting the classification of the new vector
            classification = getClassifiction(brokeBuffer);
        }else{
            classification = "invalid input";
        }

        delete[] brokeBuffer;
        char sendBuffer[4096] = {0};
        //moving the classification back to buffer for to send it back to the Client
        for (unsigned int i = 0; i < classification.length(); ++i) {
            sendBuffer[i] = classification.at(i);
        }
        //adding '\0' to the end of the string
        sendBuffer[classification.length()] = '\0';
        long send_bytes = send(client_sock, sendBuffer, classification.length(), 0);
        if (send_bytes < 0) {
            perror("error sending to Client");
        }
    }
}
        close(sock);
}



/**
 * The main function creates a Database object, and then get a new inserted vector.
 * It then finds the k nearest neighbors of that vector and classified the inserted vector
 * to be of the same classification as the biggest group inside the k nearest neighbors.
 * @param argc the number of arguments
 * @param argv the file and the port
 */
int main(int argc, char const *argv[]) {
    //checking validation of arguments.
    if(argc != 3){
        exit(1);
    }
    //checking validation of port
    if(!isPositiveInteger(argv[2]) || stoi(argv[2]) <= 0 || stoi(argv[2]) > 65535 ){
        exit(1);
    }
    //initialize the database
    auto *dataBase = initializeDatabase(argv[1], 1);

    //create a server and start a connection
    auto* server = new Server(dataBase, argv[2]);
    server->tcpSocket();
    return 0;
}