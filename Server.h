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
    int sock;
public:
    explicit Server(char const *argv[]);
    string getClassifiction(string* brokedBuffer);
    void tcpSocket();
    string* breakBuffer(char *buffer, string* brokeBuffer);
    const string &getFile() const;

};



#endif //PROJECT_SERVER_H
