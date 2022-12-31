//
// Created by Dansa on 31/12/2022.
//

#ifndef PROJECT_SERVER_H
#define PROJECT_SERVER_H

#include "classificationLogic.h"
#include "iostream"
#include <sys/socket.h>
#include <stdio.h>
#include "netinet/in.h"
#include "arpa/inet.h"
#include "unistd.h"
#include "string.h"

class Server {
private:
    string file;
    int port;
    int socket;
public:
    Server(char const *argv[]);
    string getClassifiction(const char* arr[]);
    void tcpSocket();

};







#endif //PROJECT_SERVER_H
