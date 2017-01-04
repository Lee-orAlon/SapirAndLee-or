#include "MainFlow.h"
#include "Regular.h"
#include "Luxury.h"
#include <list>

MainFlow::MainFlow() {
    this->map = createMap();
    this->taxiCenter = new TaxiCenter(map->getGrid(), new BFS(map));
    this->counter=0;
    this->numberOfDrivers = 0;
    this->addDrivers = false;
    this->clock = Clock();
   /* cin >> this->task;
    while (this->task != 7) {
        cin.ignore();
        switch (task) {
            case 1:
                this->taxiCenter->addDriver(createDriver());
                break;
            case 2: {
                this->taxiCenter->createTrip(createTrip());
                break;
            }
            case 3:
                this->taxiCenter->addCab(createCab());
                break;
            case 4:
                printDriverLocation();
                break;
            case 6: {
                this->taxiCenter->connectDriverToTaxi();
                this->taxiCenter->connectDriverToTrip();
                this->taxiCenter->moveAllDrivers();
                break;
            }
        }
        cin >> task;
    }*/
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

Driver *MainFlow::createDriver(char *driver) {
   /* int id;
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
    */

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

/*TODO*/
int MainFlow::getCounter() {
    return  this->counter;
}
/*TODO*/
int MainFlow::getNumberOfDrivers() {
    return this->numberOfDrivers;
}

/*TODO*/
int MainFlow::doUserRequest() {
    cin >> task;
    cin.ignore();
    switch (task) {
        case 1:
          //  this->taxiCenter->addDriver(createDriver());
            cin >> this->numberOfDrivers;
            cin.ignore();
            this->counter++;
            break;
        case 2: {
            this->taxiCenter->createTrip(createTrip());
            break;
        }
        case 3:
            this->taxiCenter->addCab(createCab());
            break;
        case 4:
            printDriverLocation();
            break;
      /*  case 6: {
            this->taxiCenter->connectDriverToTaxi();
            this->taxiCenter->connectDriverToTrip();
            this->taxiCenter->moveAllDrivers();
            break;
        }*/
        case 8: { /*TODO delete this case*/
            std::cout<<"try8"<<std::endl;
            break;
        }
        case 9: { /*TODO change the condition in if statement*/
            if(!this->addDrivers){
                this->taxiCenter->connectDriverToTaxi();
                this->addDrivers = true;
            } else {
                this->taxiCenter->connectDriverToTrip(this->clock.getTime());
                this->taxiCenter->moveOneStep();
            }
            this->clock.increaseTimeByOne();
            break;

        }
    }

    return this->task;
}