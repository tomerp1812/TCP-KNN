//
// Created by tomer on 1/3/23.
//

#ifndef PROJECT_CLIENT_H
#define PROJECT_CLIENT_H
using namespace std;
class Client{
private:
    int clientSocket;
    int serverPort;
    const char *serverIpAddr;
public:
    explicit Client(const string& port, const char* ipAddr);
    void initializeSocket();
    void communicate();

    int getSocket() const;

    void setSocket(int socket);
};



#endif //PROJECT_CLIENT_H
