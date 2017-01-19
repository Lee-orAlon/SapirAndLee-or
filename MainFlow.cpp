#include "MainFlow.h"
#include "Regular.h"
#include "Luxury.h"
#include <boost/log/trivial.hpp>

void* MainFlow::switchCase() {
    do {
        cin >> this->task;
        cin.ignore();
        switch (this->task) {
            case 1: {
                BOOST_LOG_TRIVIAL(debug) << "case 1- add clients" << endl;
                addThreadsAndClients();
                break;
            }
            case 2: {
                BOOST_LOG_TRIVIAL(debug) << "case 2- add trip" << endl;
                this->taxiCenter->createTrip(createTrip());
                /*if(this->isThefreConnection){
                    tcp->sendData("5");
                }*/
                break;
            }
            case 3: {
                BOOST_LOG_TRIVIAL(debug) << "case 3- add cab" << endl;
                this->taxiCenter->addCab(createCab());
                break;
            }
            case 4: {
                BOOST_LOG_TRIVIAL(debug) << "case 4- print driver's location" << endl;
                printDriverLocation();
                //if there is a connection between server to client, tell client to do nothing.
                /*if (this->isThereConnection) {
                    tcp->sendData("5"); //
                }
                 */
                break;
            }
            //case 8:{
              //  this->taxiCenter->grid->~Grid();
            //}
            case 9: {
                this->clock.increaseTimeByOne();
                //case9()

                break;
            }
            default: {
                break;
            }
        }
    } while (task != 7);
}

MainFlow::MainFlow(int port) {
    this->map = createMap();
    this->taxiCenter = new TaxiCenter(map->getGrid(), new BFS(map));
    this->clock = Clock();
    this->tcp = new Tcp(true, port);
    this->isThereConnection = false;
    //this->clients = new std::list<clientInfo *>;

    this->switchCase();

    //keep sending a close message to client until it arrives.
    //while (tcp->sendData("0") != CORRECT) {}
    delete (tcp);
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
    return new Trip(id, new Point(xStart, yStart), new Point(xEnd, yEnd), numOfPassengers, tariff,
                    time);
}

void MainFlow::printDriverLocation() {
    int id;
    cin >> id;
    cin.ignore();
    this->taxiCenter->getDriverLocation(id)->printValue();
}

MainFlow::~MainFlow() {
    clientInfo *info;
    //std::list<clientInfo *>::iterator it = this->clients->begin();
   /* while(this->clients->size()>0){
        (*it)->mainFlow=NULL;
        (*it)->center=NULL;
        this->clients->remove((*it));
        BOOST_LOG_TRIVIAL(debug) << "number of thread after deleteing" <<
                                                                       this->clients->size()<<endl;
        it++;
    }
    delete(this->clients);*/
    delete (this->taxiCenter);
    delete (this->map);
}


void MainFlow::addThreadsAndClients() {
    int numOfDrivers;
    //number of drivers
    cin >> numOfDrivers;
    this->tcp->initialize();
    char buffer[4096];
    /*
     * create trade to all driver
     */
    for (int i = 0; i < numOfDrivers; i++) {
        pthread_t thread;
        int socket = this->tcp->acceptOneClient();
        this->tcp->receiveData(buffer, sizeof(buffer), socket);
        int ID = this->taxiCenter->getIDFromSerialization(buffer,buffer + 4095);
        //initialize one struct to the customer
        clientInfo *info = new clientInfo;
        info->clientSocket = socket;
        info->clientID = ID;
        info->mainFlow = this;
        info->center = this->taxiCenter;
        //recive string of cab
        string dataTaxi = this->taxiCenter->connectDriverToTaxi(buffer, buffer + 4095);
        // send serialized cab to the driver.
        this->tcp->sendData(dataTaxi, socket);
        //create thread
        int check = pthread_create(&thread, NULL, case9, (void*)info);
        if(!check){
        //    pthread_join(thread, NULL);
        } else {
            /*TODO exit*/
        }
    }
    //set that the socket is open (there is a connection).
    this->isThereConnection = true;
}


/*TODO*/
void *MainFlow::case9(void *information) {
    //recive information from the threade
    clientInfo *info = (clientInfo*)information;
    //print it that we arrive to one thread
    BOOST_LOG_TRIVIAL(debug) << "case 9" << endl;
    char buffer[4096];
    //this->tcp->reciveData(buffer, sizeof(buffer));
    int lastTime = -1;
    string path;
    /*
     * while the customer not ener 7 ,the thread alive and perform things according to the
     * times
     */
    while (info->mainFlow->getTask() != 7) {
        //need to delete?
     //   for (std::list<clientInfo *>::iterator client = info->mainFlow->clients->begin();
       //      client != info->mainFlow->clients->end(); client++) {
        //    bool move = info->center->moveOneStep(info->mainFlow->clock.getTime(),
          //                                        (*client)->clientID);

        //check if the time change
            if(lastTime!=info->mainFlow->clock.getTime()) {
                //if time change update the time
                lastTime = info->mainFlow->clock.getTime();
                //print the current time
                BOOST_LOG_TRIVIAL(debug) << "time is: " << info->mainFlow->clock.getTime() << endl;
                //move the driver
                bool move = info->center->moveOneStep(info->mainFlow->clock.getTime(),
                                                      info->clientID);
                /*
                 * Need to complete
                 */
                if (move) {
                    //tcp->sendData("9", (*client)->clientSocket); //tell client to move.
                    /*string currentLoc = info->center->getCurrentLocationAndSerializeIt(info->clientID);
                    BOOST_LOG_TRIVIAL(debug) << "send: " << currentLoc << endl;
                    if(currentLoc.compare("NULL") != 0) {
                        int byt = info->mainFlow->tcp->sendData(currentLoc, info->clientSocket);
                        BOOST_LOG_TRIVIAL(debug) << "sent: " << byt << endl;*/
                   // }
                } else {
                    //tcp->sendData("5"); //tell client to do nothing.
                }
                /*
                 * connect trips to driver,all the time cheak if there trips wuthout driver
                 * if  there is that trips'we ant the current time big or equal to the time of trip
                 * so explore driver
                 */
                do {
                    path = info->center->serializePath(info->mainFlow->clock.getTime());
                    if (path.compare("NULL") != 0) {
                        //tell client to deserialize the given path.
                        //this->tcp->sendData("2", (*client)->clientSocket);
                        //this->tcp->sendData(path, (*client)->clientSocket);
                    }
                } while (path.compare("NULL") != 0);

                if (path.compare("NULL") == 0) {
                    //tcp->sendData("5", (*client)->clientSocket); //tell client to do nothing.
                }
            }
      //  }
    }
   // info->mainFlow->tcp->sendData("0", info->clientSocket);
}

/*
 * get the number of current task
 */
int MainFlow::getTask() {
    return this->task;
}
