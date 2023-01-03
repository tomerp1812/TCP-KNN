#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Client.h"
#include <cstring>


/**
 * If the string is empty or the first character is not a digit, then it's not a positive integer. Otherwise, it's a
 * positive integer if the string is equal to the number converted to a string
 *
 * @param s The string to be checked
 *
 * @return A boolean value.
 */
bool isPositiveInteger(const string &s) {
    if (s.empty() || ((!isdigit(s[0])))) return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

/**
 * It creates a new client object, initializes the socket, and then communicates with the server
 *
 * @param argc the number of arguments passed to the program
 * @param argv
 *
 * @return The return value of the function.
 */
int main(int argc, char const *argv[]) {
    //checks if there are 2 argument put.
    if (argc != 3) {
        cout << "Invalid input!" << endl;
        exit(1);
    }
    auto* client = new Client(argv[2], argv[1]);
    //initialize connection to server
    client->initializeSocket();
    client->communicate();
    return 0;
}

/**
 * This function takes in a port number and an IP address and sets the serverPort and serverIpAddr variables to the values
 * passed in
 *
 * @param port The port number of the server.
 * @param ipAddr The IP address of the server.
 */
Client::Client(const string& port, const char* ipAddr) {
    if(!isPositiveInteger(port) || stoi(port) <= 0 || stoi(port) > 65535 ){
        exit(1);
    }
    this->serverPort = stoi(port);
    this->serverIpAddr = ipAddr;
    //default socket
    this->clientSocket = -1;
}

/**
 * It returns the socket of the client.
 *
 * @return The client socket.
 */
int Client::getSocket() const {
    return clientSocket;
}

/**
 * This function sets the clientSocket variable to the socket passed in as a parameter.
 *
 * @param socket The socket that the client is connected to.
 */
void Client::setSocket(int socket) {
    this->clientSocket = socket;
}

/**
 * This function creates a socket and connects it to the server
 */
void Client::initializeSocket() {
    setSocket((int)socket(AF_INET, SOCK_STREAM, 0));

    //checking creation succeed
    if (getSocket() < 0){
        cout << "error creating sock" << endl;
        exit(1);
    }

    //for sending a group of parameters and get them back we create a struct
    struct sockaddr_in sin;
    //nullify the struct
    memset(&sin, 0, sizeof (sin));
    //initialize the struct fields
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverIpAddr);
    sin.sin_port = htons(serverPort);
    if(connect(getSocket(), (struct sockaddr *) &sin, sizeof(sin)) < 0){
        cout << "error connecting to server" << endl;
        exit(1);
    }

}

/**
 * It takes in a string from the user, sends it to the server, and then prints out the response from the server
 */
void Client::communicate() {
    while(true){
        //set a buffer to hold the incoming data
        char data_addr[4096] = {0};
        string str;
        getline(cin, str);
        str.copy(data_addr, str.length(), 0);
        int data_len = (int) strlen(data_addr);
        long sent_bytes = send(getSocket(), data_addr, data_len, 0);
        if(str == "-1"){
            close(getSocket());
            break;
        }
        if(sent_bytes < 0){
            cout << "ERROR" << endl;
            exit(1);
        }
        char buffer[4096] = {0};
        int expected_data_len = sizeof(buffer);
        long read_bytes = recv(getSocket(), buffer, expected_data_len, 0);
        if(read_bytes == 0){
            continue;
        }
        else if (read_bytes < 0){
            cout << "ERROR" << endl;
            exit(1);
        }
        else {
            cout << buffer << endl;
            continue;
        }
        close(getSocket());
        break;
    }
}