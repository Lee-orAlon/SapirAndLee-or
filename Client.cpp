#include "Client.h"
#include "Udp.h"
#include "Driver.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
using namespace std;

Driver * createDriver();
string serializeDriver(Driver* d);
Cab* deserializeCab(string cab);
Trip* desirializeTrip(string trip);

int main(int argc, char**argv) {
    if (argc == 3) {
        Driver *driver;
        Udp *udp = new Udp(false, atoi(argv[2]), argv[1]);
        if(udp->initialize()!=CORRECT){
            perror("error creating socket");
        }

        driver= createDriver();
        udp->sendData(serializeDriver(driver));
       /* if(udp.sendData(driver)!=CORRECT){
            perror("error writing to socket");
        }*/

        //receive serialized cab from server.
        char buffer[4096];
        udp->reciveData(buffer, sizeof(buffer));
        deserializeCab(buffer);
//        if(udp.reciveData(buffer,4096)!=-1){
  //      deserializeCab(buffer);
      //  }

        string closeSocket = "close";
        bool socketOpen = true;

        while (socketOpen) {
            udp->sendData("send me data");
            udp->reciveData(buffer, sizeof(buffer));
            cout << "The server sent: " << buffer << endl;
            if(buffer == "move"){

            }
            if(buffer == "trip"){

            }
            if(buffer == "path"){

            }
//            if(udp.reciveData(buffer,4096)!=-1) {
              //  if (buffer == "trip") {
                //    if (udp->reciveData(buffer, 4096) != -1) {
                  //      Trip *trip = desirializeTrip(buffer);
                       // driver->setTrip(trip);
                 //   }
             //   }
              /*  if (buffer == "move") {
                    if (udp->reciveData(buffer, 4096) != -1) {
                        /*TODO move*/
                   // }
              //  }
                if (closeSocket.compare(buffer) == 0) {
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

Cab* deserializeCab(string cab){
   Cab *newCab;
    boost::iostreams::basic_array_source<char> device(cab.c_str(), cab.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >>newCab;
    return  newCab;

}

Trip* desirializeTrip(string trip){
    Trip *newTrip;
    boost::iostreams::basic_array_source<char> device(trip.c_str(), trip.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >>newTrip;
    return  newTrip;

}