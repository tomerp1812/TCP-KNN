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
    Database* database;
    int port;
    int sock;
public:
    explicit Server(Database* database, const string& port);
    string getClassifiction(string* brokeBuffer);
    void tcpSocket();
    bool breakBuffer(char *buffer, string* brokeBuffer);

};



#endif //PROJECT_SERVER_H
