#include "Client.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
using namespace std;
int main(int argc, char**argv) {
    if (argc == 3) {
        int sent_bytes;
        int bytes;
        string closeSocket = "close";
        const char *ip_address = argv[1];
        const int port_no = atoi(argv[2]);
        int sock = socket(AF_INET, SOCK_DGRAM, 0);
        if (sock < 0) {
            perror("error creating socket");
        }
        struct sockaddr_in sin;
        memset(&sin, 0, sizeof(sin));
        sin.sin_family = AF_INET;
        sin.sin_addr.s_addr = inet_addr(ip_address);
        sin.sin_port = htons(port_no);
        char data[] = "hello!";
        int data_len = sizeof(data);
        bool socketOpen = true;

        while (socketOpen) {
            sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
            if (sent_bytes < 0) {
                perror("error writing to socket");
            }
            if (sent_bytes==EPIPE){
                socketOpen = false;
            }
            struct sockaddr_in from;
            unsigned int from_len = sizeof(struct sockaddr_in);
            char buffer[4096];
            bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from,
                             &from_len);
            if (bytes < 0) {
                perror("error reading from socket");
            }
            if (bytes == 0){
                socketOpen = false;
            }
            if(closeSocket.compare(buffer)==0){
                socketOpen = false;
            }
            cout << "The server sent: " << buffer << endl;
        }
        close(sock);
        return 0;
    }
}