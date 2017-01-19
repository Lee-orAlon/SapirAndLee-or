#include "Client.h"
#include "Tcp.h"
#include "Driver.h"

using namespace std;

Value* deserializeLocation(char * loc, char* end);

/**
 * createDriver- create new driver according to the user's input.
 */
Driver *createDriver();

/**
 * serializeDriver.
 * @param d the driver that the user wants to serialize.
 * @return the seralization of the given driver (a string of the driver's information).
 */
string serializeDriver(Driver *d);

int main(int argc, char **argv) {
    //project name,port number,ip address -three parameters
    if (argc == 3) {
        Driver *driver;
        Tcp *tcp = new Tcp(false, atoi(argv[2]));
        if (tcp->initialize() != 1) {
            perror("error creating socket");
        }
        driver = createDriver();
        string driverStr = serializeDriver(driver);
        //send the serialization of the driver to the server.
//        int descriptor = tcp->acceptOneClient();
        tcp->sendData(driverStr, 0);
        char buffer[4096];
        //receive the serialized cab from server.
        tcp->receiveData(buffer, sizeof(buffer),0);
        //add the cab to driver.
        Cab *cab = driver->deserializeCab(buffer, buffer + 4095);
        driver->setCab(cab);

        bool socketOpen = true;
        tcp->sendData("send me data", 0);
        while (socketOpen) {
            tcp->receiveData(buffer, sizeof(buffer),0);
            if(atoi(buffer) == 0) {
                socketOpen = false;
            } else {
                driver->setLocation(deserializeLocation(buffer, buffer+4095));
            }
           // int command = atoi(buffer);
            /*switch (command) {
                case 0: {//if server sent "0" then communication end- close socket.
                    socketOpen = false;
                    break;
                }
                case 2: {//if server sent "2" than add path to driver.
                    //tcp->reciveData(buffer, sizeof(buffer));
                    driver->enterPath(buffer, buffer + 4095);
                    //tcp->sendData("ok", descriptor);
                    break;
                }
                case 9: {//if server sent "9" - move.
                    if (driver->isInTrip()) {
                        driver->doNextMove();
                    }
                    tcp->sendData(driver->serializeMyLocation(), 0);
                    break;
                }
                default: {
                    //tcp->sendData("send me data", descriptor);
                }
            }*/
        }
        delete (cab);
        delete (driver);
        return 0;
    }
}

Driver *createDriver() {
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

string serializeDriver(Driver *d) {
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << d;
    s.flush();
    return serial_str;
}


Value* deserializeLocation(char * loc,char* end){
    Value * location;
    boost::iostreams::basic_array_source<char> device(loc,end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> location;

    return location;
}

