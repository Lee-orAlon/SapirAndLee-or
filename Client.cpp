#include "Client.h"
#include "Udp.h"
#include "Driver.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "Element.h"
using namespace std;

Driver * createDriver();
string serializeDriver(Driver* d);
Cab *deserializeCab(char *cab, char *end);
std::list<Element*> *desirializePath(char *trip, char *end);

int main(int argc, char**argv) {
    if (argc == 3) {
        Driver *driver;
        Udp *udp = new Udp(false, atoi(argv[2]), argv[1]);
        if(udp->initialize()!=CORRECT){
            perror("error creating socket");
        }

        driver= createDriver();
        string driverStr = serializeDriver(driver);
        udp->sendData(driverStr);
        /* if(udp.sendData(driver)!=CORRECT){
             perror("error writing to socket");
         }*/

        //receive serialized cab from server.
        char buffer[4096];
        udp->reciveData(buffer, sizeof(buffer));
        deserializeCab(buffer, buffer+4095);
//        if(udp.reciveData(buffer,4096)!=-1){
        //      deserializeCab(buffer);
        //  }

        string closeSocket = "close";
        string recievePath = "path";
        string data;
        bool socketOpen = true;

        while (socketOpen) {
            udp->sendData("send me data");
            udp->reciveData(buffer, sizeof(buffer));
            cout << "The server sent: " << buffer << endl;
            //if server sent "2" than add path to driver.
            if(buffer[0]=='2'){
                udp->reciveData(buffer, sizeof(buffer));
                std::list<Element*> *path = desirializePath(buffer, buffer+4095);
                driver->enterPath(buffer, buffer+4095);
            }
//            if(udp.reciveData(buffer,4096)!=-1) {
            //  if (buffer == "trip") {
            //    if (udp->reciveData(buffer, 4096) != -1) {
            //      Trip *trip = desirializePath(buffer);
            // driver->setTrip(trip);
            //   }
            //   }
            /*  if (buffer == "move") {
                  if (udp->reciveData(buffer, 4096) != -1) {
                      /*TODO move*/
            // }
            //  }
            //if servre sent "0" then communication end- close socket.
            if (buffer[0]=='0') {
                socketOpen = false;
            }

            //  }
        }
        //close socket
//        delete (udp);
        return 0;
    }
}

Driver * createDriver() {
    int id;
    int age;
    char status;
    int experience;
    int cabID;
    char dummy;

    cin >> id;
    cin >> dummy;
    cin >> age;
    cin >> dummy;
    cin >> status;
    cin >> dummy;
    cin >> experience;
    cin >> dummy;
    cin >> cabID;
    cin.ignore();
    return new Driver(id, age, status, experience, cabID);
}

string serializeDriver(Driver* d){
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << d;
    s.flush();


    return serial_str;
}
Cab *deserializeCab(char *cab, char *end) {
    if(cab!="NULL") {
        Cab *newCab;
        boost::iostreams::basic_array_source<char> device(cab, end);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> newCab;
        return newCab;
    }

}

std::list<Element*> *desirializePath(char *path, char *end) {
    std::list<Element*> *listElm;
    boost::iostreams::basic_array_source<char> device(path, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >>listElm;
    return  listElm;

}