#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Client.h"
#include <cstdio>
#include <cstring>


bool isPositiveInteger(const string &s) {
    if (s.empty() || ((!isdigit(s[0])))) return false;

    char *p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        cout << "Invalid input!" << endl;
        exit(1);
    }
    auto* client = new Client(argv[2], argv[1]);
    client->initializeSocket();
    client->communicate();
    return 0;
}

Client::Client(const string& port, const char* ipAddr) {
    if(!isPositiveInteger(port) || stoi(port) <= 0 || stoi(port) > 65535 ){
        exit(1);
    }
    this->serverPort = stoi(port);
    this->serverIpAddr = ipAddr;
    this->clientSocket = -1;
}

int Client::getSocket() const {
    return clientSocket;
}

void Client::setSocket(int socket) {
    this->clientSocket = socket;
}

void Client::initializeSocket() {
    setSocket((int)socket(AF_INET, SOCK_STREAM, 0));

    if (getSocket() < 0){
        cout << "error creating sock" << endl;
        exit(1);
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof (sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(serverIpAddr);
    sin.sin_port = htons(serverPort);
    if(connect(getSocket(), (struct sockaddr *) &sin, sizeof(sin)) < 0){
        cout << "error connecting to server" << endl;
        exit(1);
    }

}

void Client::communicate() {
    while(true){
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
