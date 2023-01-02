//
// Created by Tomer on 01/12/2022.
//



#include "Server.h"

Server::Server(Database* dB, const string& port) {
    this->database = dB;
    this->port = stoi(port);
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
}


// To do!!!!!!!!!!!!!!!!!!!!!
//send right arguments by the new order
string Server::getClassifiction(string* data) {
    //old order:
    //argv[1] = k
    //argv[2] = file
    //argv[3] = Distance

    //new order:
    //arr[0] = vector
    //arr[1] = distance
    //arr[2] = k

    //??? the new vector is now inserted with the arguments???
    //??? meaning need to call create vector from here or to change it???
//    int k = stoi(data[2]);
//    //initialize the database
//    auto *dataBase = initializeDatabase(file, k);

    database->setK(stoi(data[2]));

    //choose the distance algorithm
    char* disAlg = new char[data[1].length() + 1];
    data[1].copy(disAlg, data[1].length(), 0);
    disAlg[data[1].length()] = '\0';
    Distance *dis = chooseDis(disAlg);
    if (dis == nullptr){
        return "invalid input";
    }
    delete[] disAlg;

    //return  a new classified vector
    return newVectorClassification(this->database, dis, data[0]);

}

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
    || buffer[i] == '.' || buffer[i] == 'E')
    {
        vectorString += buffer[i];
        i++;
    }
    //vectorString.at(vectorString.length() - 1) = '\0';
    if(!checkStr(vectorString)){
        return false;
    }
    brokeBuffer[0] = vectorString;
    if(input.length() - brokeBuffer[0].length() < 5){
        return false;
    }

    // create second string - distance (a 3 letters word)
    string distanceString;
    for (int j = 0; j < 3; j++)
    {
        distanceString += buffer[i];
        i++;
    }
    brokeBuffer[1] = distanceString;
    i++;
    // create third string - k (a number)
    string kString;
    while (buffer[i] != '\0')
    {
        kString += buffer[i];
        i++;
    }
    if(!isPositiveInteger(kString)){
        return false;
    }
    brokeBuffer[2] = kString;
    return true;
}

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
    //accept an incoming client connection
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
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
        if(brokeBuffer[0] == "-1" && brokeBuffer->length() == 2){
            break;
        }
        if(breakBuffer(buffer, brokeBuffer)){
            //getting the classification of the new vector
            classification = getClassifiction(brokeBuffer);
            delete[] brokeBuffer;
        }else{
            classification = "invalid input";
        }


        char sendBuffer[4096] = {0};
        //moving the classification back to buffer for to send it back to the client
        for (unsigned int i = 0; i < classification.length(); ++i) {
            sendBuffer[i] = classification.at(i);
        }
        //adding '\0' to the end of the string
        sendBuffer[classification.length()] = '\0';
        long send_bytes = send(client_sock, sendBuffer, classification.length(), 0);
        if (send_bytes < 0) {
            perror("error sending to client");
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
 * @param argv
 * @return The name of the closest point to the input vector.
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
    auto* server = new Server(dataBase, argv[2]);
    server->tcpSocket();
    return 0;
}