#include "Client.h"
#include "Udp.h"
#include "Driver.h"

using namespace std;

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
        Udp *udp = new Udp(false, atoi(argv[2]), argv[1]);
        if (udp->initialize() != CORRECT) {
            perror("error creating socket");
        }
        driver = createDriver();
        string driverStr = serializeDriver(driver);
        //send the serialization of the driver to the server.
        udp->sendData(driverStr);
        char buffer[4096];
        //receive the serialized cab from server.
        udp->reciveData(buffer, sizeof(buffer));
        //add the cab to driver.
        Cab *cab = driver->deserializeCab(buffer, buffer + 4095);
        driver->setCab(cab);

        bool socketOpen = true;
        udp->sendData("send me data");
        while (socketOpen) {
            udp->reciveData(buffer, sizeof(buffer));
            int command = atoi(buffer);
            switch (command) {
                case 0: {//if server sent "0" then communication end- close socket.
                    socketOpen = false;
                    break;
                }
                case 2: {//if server sent "2" than add path to driver.
                    udp->reciveData(buffer, sizeof(buffer));
                    driver->enterPath(buffer, buffer + 4095);
                    udp->sendData("ok");
                    break;
                }
                case 9: {//if server sent "9" - move.
                    if (driver->isInTrip()) {
                        driver->doNextMove();
                    }
                    udp->sendData("ok");
                    break;
                }
                default: {
                    udp->sendData("send me data");
                }
            }
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

