//
// Created by Tomer on 01/12/2022.
//



#include "Server.h"

Server::Server(char const *argv[]) {
    this->file = argv[1];
    this->port = stoi(argv[2]);
    this->sock = socket(AF_INET, SOCK_STREAM, 0);
}

const string &Server::getFile() const {
    return file;
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

    int k = stoi(data[2]);
    //initialize the database
    auto *dataBase = initializeDatabase(file, k);

    //choose the distance algorithm
    char* disAlg = new char[data[1].length() + 1];
    data[1].copy(disAlg, data[1].length(), 0);
    disAlg[data[1].length()] = '\0';
    Distance *dis = chooseDis(disAlg);
    delete[] disAlg;

    //return  a new classified vector
    return newVectorClassification(dataBase, dis);

}

string* Server::breakBuffer(char *buffer, string* brokedBuffer) {
    // create first string - vector
    string vectorString;
    int i = 0;
    while ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == ' ')
    {
        vectorString += buffer[i];
        i++;
    }
    brokedBuffer[0] = vectorString;

    // create second string - distance (a 3 letters word)
    string distanceString;
    for (int j = 0; j < 3; j++)
    {
        distanceString += buffer[i];
        i++;
    }
    brokedBuffer[1] = distanceString;

    // create third string - k (a number)
    string kString;
    while (buffer[i] != '\n')
    {
        kString += buffer[i];
        i++;
    }
    brokedBuffer[2] = kString;

    return brokedBuffer;
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

    //accept an incoming client connection
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin);
    int client_sock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
    }

    //set a buffer to hold the incoming data
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    long read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes == 0){
        cout << "Connection is closed" << endl;
    }else if  (read_bytes < 0){
        perror("error in receiving data");
    }else{
        //buffer stores the received data! (vector, distance, k)
        cout << buffer << endl;
    }

    // convert buffer into array of 3 strings and send it to getClassification
    string* brokedBuffer = new string[3];
    breakBuffer(buffer, brokedBuffer);
    //getting the classification of the new vector
    string classification = getClassifiction(brokedBuffer);
    delete[] brokedBuffer;

    //moving the classification back to buffer for to send it back to the client
    for (int i = 0; i < classification.length(); ++i) {
        buffer[i] = classification.at(i);
    }
    //adding '\0' to the end of the string
    buffer[classification.length()] = '\0';

    long send_bytes = send(client_sock, buffer, read_bytes, 0);
    if (send_bytes < 0){
        perror("error sending to client");
    }

    close (sock);
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

    auto* server = new Server(argv);
    server->tcpSocket();
    return 0;

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    





}


