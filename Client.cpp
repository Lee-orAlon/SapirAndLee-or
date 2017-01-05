#include "Client.h"
#include "Udp.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
using namespace std;
int main(int argc, char**argv) {
    if (argc == 3) {
        Udp udp = Udp(false, atoi(argv[2]), argv[1]);
        if(udp.initialize()!=CORRECT){
            perror("error creating socket");
        }

        /*TODO create driver*/

        string driver;
        if(udp.sendData(driver)!=CORRECT){
            perror("error writing to socket");
        }

        //receive serialized cab from server.
        char* buffer;
        if(udp.reciveData(buffer,4096)!=-1){
            /*TODO deserialize cab*/
        }

        string closeSocket = "close";
        bool socketOpen = true;

        while (socketOpen) {
            if(udp.reciveData(buffer,4096)!=-1){
                if(buffer=="trip"){
                    if(udp.reciveData(buffer,4096)!=-1){
                        /*TODO */
                    }
                }
                if(buffer=="move"){
                    if(udp.reciveData(buffer,4096)!=-1){
                        /*TODO move*/
                    }
                }
            }
            if(closeSocket.compare(buffer)==0){
                socketOpen = false;
            }
            cout << "The server sent: " << buffer << endl;
        }
        //close socket
        delete (udp);
        return 0;
    }
}