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
//create new driver
Driver * createDriver();
//make serilizazia to driver
string serializeDriver(Driver* d);
Cab *deserializeCab(char *cab, char *end);
//make desirloze to list that contain path of path of driver
//std::list<Element*> *desirializePath(char *trip, char *end);

int main(int argc, char**argv) {
    //project name,port number,ip address -three parameters
    if (argc == 3) {
        Driver *driver;
        Udp *udp = new Udp(false, atoi(argv[2]), argv[1]);
        if(udp->initialize()!=CORRECT){
            perror("error creating socket");
        }
        driver= createDriver();
        string driverStr = serializeDriver(driver);
        //send the serloze of the driver to server
        udp->sendData(driverStr);
        char buffer[4096];
        //recive the serloze of cab
        udp->reciveData(buffer, sizeof(buffer));
        //add the cab to driver
        Cab *cab = deserializeCab(buffer, buffer+4095);
        driver->setCab(cab);
        bool socketOpen = true;
        udp->sendData("send me data");
        while (socketOpen) {
            udp->reciveData(buffer, sizeof(buffer));
            int command = atoi(buffer);
            switch (command){
                case 0: {//if server sent "0" then communication end- close socket.
                    socketOpen = false;
                    break;
                }
                case 2:{//if server sent "2" than add path to driver.
                    udp->reciveData(buffer, sizeof(buffer));
                    //std::list<Element*> *path = desirializePath(buffer, buffer+4095);
                    driver->enterPath(buffer, buffer+4095);
                    udp->sendData("ok");
                    break;
                }
                case 9:{//if server sent "9" - move.
                    if(driver->isInTrip()) {
                        driver->doNextMove();
                    }
                    udp->sendData("ok");
                    break;
                }
                default:{
                    udp->sendData("send me data");
                }
            }
        }
        delete(cab);
        delete(driver);
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

/*std::list<Element*> *desirializePath(char *path, char *end) {
    std::list<Element*> *listElm;
    boost::iostreams::basic_array_source<char> device(path, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >>listElm;
    return  listElm;


}*/