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
string Server::getClassifiction(const char* arr[]) {
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

    int k = stoi(arr[2]);
    //initialize the database
    auto *dataBase = initializeDatabase(file, k);

    //choose the distance algorithm
    const char *disAlg = arr[1];
    Distance *dis = chooseDis(disAlg);

    //return  a new classified vector
    return newVectorClassification(dataBase, dis);

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
    //To do !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //getting the classification of the new vector
    //string classification = getClassifiction();

    //moving the classification back to buffer for to send it back to the client
    //To do!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

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


