#include <iostream>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>




using namespace std;

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        cout << "Invalid input!" << std::endl;
        exit(1);
    }
    const char* ip_address = argv[1];
    const int port_number = stoi(argv[2]);
    int sock = (int)socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        cout << "error creating sock" << endl;
    }
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof (sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_number);
    if(connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0){
        cout << "error connecting to server" << endl;
        exit(1);
    }
    while(true){
        char* data_addr[4096];
        scanf("%s", *data_addr);
        cout << data_addr;
        int data_len = (int) strlen(*data_addr);
        int sent_bytes = send(sock, *data_addr, data_len, 0);
        if(sent_bytes < 0){
            cout << "ERROR" << endl;
            exit(1);
        }
        char buffer[4096];
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if(read_bytes == 0){
            cout << "continue";
        }
        else if (read_bytes < 0){
            cout << "ERROR" << endl;
            exit(1);
        }
        else {
            cout << buffer;
        }
        close(sock);
        break;
    }

    return 0;
}
