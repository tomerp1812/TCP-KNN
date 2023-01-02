//
// Created by tomer on 1/3/23.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H

class Client{
private:
    int clientSocket;
    int serverPort;
    const char *serverIpAddr;
public:
    explicit Client(const std::string& port, const char* ipAddr);
    void initializeSocket();
    void communicate();

    int getSocket() const;

    void setSocket(int socket);
};



#endif //PROJECT_CLIENT_H
