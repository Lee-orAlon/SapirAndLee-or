#include "MainFlow.h"
#include "Regular.h"
#include "Luxury.h"

MainFlow::MainFlow(int port) {
    this->map = createMap();
    this->taxiCenter = new TaxiCenter(map->getGrid(), new BFS(map));
    this->clock = Clock();
    this->udp = new Udp(true,port);
    this-> isThereConnection = false;

    do{
        cin >> this->task;
        cin.ignore();
        switch (this->task) {
            case 1: {
                int numOfDrivers;
                cin>>numOfDrivers;
                this->udp->initialize();
                char buffer[4096];
                this->udp->reciveData(buffer, sizeof(buffer));
                string dataTaxi = this->taxiCenter->connectDriverToTaxi(buffer, buffer+4095);
                // send serialized cab to the driver.
                this->udp->sendData(dataTaxi);
                //set that the socket is open (there is a connection.
                this->isThereConnection = true;
                break;
            } case 2: {
                this->taxiCenter->createTrip(createTrip());
                if(this->isThereConnection){
                    udp->sendData("5");
                }
                break;
            }
            case 3: {
                this->taxiCenter->addCab(createCab());
                break;
            }
            case 4: {
                printDriverLocation();
                //if there is a connection between server to client, tell client to do nothing.
                if (this->isThereConnection) {
                    udp->sendData("5"); //
                }
                break;
            }
            case 9: {
                char buffer[4096];
                this->udp->reciveData(buffer, sizeof(buffer));
                this->clock.increaseTimeByOne();
                string path;
                do{
                    path = this->taxiCenter->serializePath(this->clock.getTime());
                    if(path.compare("NULL")!=0) {
                        this->udp->sendData("2");//tell client to deserialize the given path.
                        this->udp->sendData(path);
                    }
                } while(path.compare("NULL")!=0);

                if(path.compare("NULL")==0){
                    udp->sendData("5"); //tell client to do nothing.
                }
                bool move = this->taxiCenter->moveOneStep(this->clock.getTime());
                if(move) {
                    udp->sendData("9"); //tell client to move.
                } else {
                    udp->sendData("5"); //tell client to do nothing.
                }
                break;
            }
            default: {
                break;
            }
        }
    } while (this->task!=7);

    //keep sending a close message to client until it arrives.
    while (udp->sendData("0")!=CORRECT){}
    delete (udp);
}

Map *MainFlow::createMap() {
    int xSize;
    int ySize;
    int numOfObstacles;
    char dummy;
    std::list<Value *> obstacles;

    cin >> xSize;
    cin >> ySize;
    cin.ignore();
    cin >> numOfObstacles;
    cin.ignore();
    if (numOfObstacles > 0) {
        int xValue;
        int yValue;
        for (int i = 0; i < numOfObstacles; i++) {
            cin >> xValue >> dummy >> yValue;
            cin.ignore();
            obstacles.push_back(new Point(xValue, yValue));
        }
    }
    std::list<int> *sizes = new std::list<int>;
    sizes->push_back(xSize);
    sizes->push_back(ySize);
    Map *m = new Map(obstacles, sizes);
    delete (sizes);
    return m;
}

Cab *MainFlow::createCab() {
    int id;
    int type;
    char manufacturer;
    char colour;
    char dummy;

    cin >> id;
    cin >> dummy;
    cin >> type;
    cin >> dummy;
    cin >> manufacturer;
    cin >> dummy;
    cin >> colour;
    cin.ignore();
    if (type == 1) {
        return new Regular(id, colour, manufacturer);
    }
    if (type == 2) {
        return new Luxury(id, colour, manufacturer);
    }
}

Passenger *MainFlow::createPassenger() {
}

Trip *MainFlow::createTrip() {
    int id;
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    int numOfPassengers;
    double tariff;
    int time;
    char dummy;

    cin >> id;
    cin >> dummy;
    cin >> xStart;
    cin >> dummy;
    cin >> yStart;
    cin >> dummy;
    cin >> xEnd;
    cin >> dummy;
    cin >> yEnd;
    cin >> dummy;
    cin >> numOfPassengers;
    cin >> dummy;
    cin >> tariff;
    cin >> dummy;
    cin >> time;
    cin.ignore();
    return new Trip(id, new Point(xStart, yStart), new Point(xEnd, yEnd), numOfPassengers, tariff,time);
}

void MainFlow::printDriverLocation() {
    int id;
    cin >> id;
    cin.ignore();
    this->taxiCenter->getDriverLocation(id)->printValue();
}

MainFlow::~MainFlow() {
    delete (this->taxiCenter);
    delete (this->map);
}
