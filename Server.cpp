#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "MainFlow.h"

using namespace std;

int main(int argc, char**argv) {
    int bytes;
    int sent_bytes;
    MainFlow *mainFlow = new MainFlow();
    int task;
    const int server_port = atoi(argv[1]);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(server_port);

    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }

    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);


    char buffer[4096];
    char *data= "yay! :)";

    bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from,
                     &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    do{
        task =mainFlow->doUserRequest();
        if((task==1)&&(mainFlow->getCounter()==1)) {
            int numOfDrivers = mainFlow->getNumberOfDrivers();
            for(int i=0; i<numOfDrivers; i++) {
                bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from,
                                 &from_len);
                if (bytes < 0) {
                    perror("error reading from socket");
                }

                cout << "The client sent: " << buffer << endl;

                /*TODO deserialization*/
                //mainFlow->createDriver(buffer);
            }
        }
        sent_bytes = sendto(sock, data, sizeof(data), 0, (struct sockaddr *) &from, sizeof(from));
        if (sent_bytes < 0) {
            perror("error writing to socket1");
        }

    } while (task != 7);
    //send closing message to client.
    data = "close";
    sent_bytes = sendto(sock, data, sizeof(data), 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }
    close(sock);

    return 0;
}