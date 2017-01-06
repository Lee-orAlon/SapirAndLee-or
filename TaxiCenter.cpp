#include "TaxiCenter.h"

using namespace std;

TaxiCenter::TaxiCenter(Grid *grid, BFS *bfs) {
    this->bfs = bfs;
    this->cabs = new std::list<Cab *>;
    this->drivers = new std::list<Driver *>;
    this->grid = grid;
    this->trip = new std::list<Trip *>;
}

TaxiCenter::TaxiCenter() {
}

TaxiCenter::~TaxiCenter() {
    Driver *driver;
    for (std::list<Driver *>::iterator it = this->drivers->begin();
         it != this->drivers->end(); it++) {
        driver = (*it);
        (*it) = NULL;
        delete (driver);
    }
    delete this->drivers;
    Cab *cab;
    for (std::list<Cab *>::iterator itCab = this->cabs->begin();
         itCab != this->cabs->end(); itCab++) {
        cab = (*itCab);
        (*itCab) = NULL;
        delete (cab);
    }
    delete (this->cabs);
    Trip *trip;
    for (std::list<Trip *>::iterator itTrip = this->trip->begin();
         itTrip != this->trip->end(); itTrip++) {
        trip = (*itTrip);
        (*itTrip) = NULL;
        delete (trip);
    }
    delete (this->trip);
    delete (this->grid);
    delete this->bfs;
}

std::list<Driver *> *TaxiCenter::listOfDriver() {
    return this->drivers;
}


void TaxiCenter::createTrip(Trip *t) {
    this->trip->push_back(t);
}

Trip *TaxiCenter::connectDriverToTrip(int currntTime) {
    std::list<Trip *>::iterator it = this->trip->begin();
    for (std::list<Trip *>::iterator it = this->trip->begin();
         it != this->trip->end(); it++) {
        if (((*it)->getStartTime() == currntTime) && ((*it)->doesTripHasDriver() == false)) {
            Driver *d = this->findClosestDriver((*it)->getStart());
            if (d != NULL) {
                (*it)->setTripHasDriverToBeTrue();
                d->setTrip(*it);

                std::list<Element *> *pathD = this->bfs->pathDrive((*it)->getStart(),
                                                                   (*it)->getEnd());
                pathD->remove(*pathD->begin());
                d->setPath(pathD);
                (*it)->setTripHasDriverToBeTrue();
                return (*it);
            }
        }
    }
    return NULL;
}

string TaxiCenter::serializePath(int currentTime) {
    Trip *trip = this->connectDriverToTrip(currentTime);
    if (trip != NULL) {
        std::list<Element *> *path = this->createPath(trip->getStart(), trip->getEnd());
        path->remove(*path->begin());
        std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << path;
        s.flush();
        delete (path);
        return serial_str;
    }
    return "NULL";
}

std::list<Trip *> *TaxiCenter::listOfTrip() {
    return this->trip;
}

Driver *TaxiCenter::findClosestDriver(Value *location) {
    if (this->drivers != NULL) {
        Driver *closest;
        double distance;
        double currentDistance;
        distance = -1;
        std::list<Driver *>::iterator it = this->drivers->begin();

        for (std::list<Driver *>::iterator it = this->drivers->begin();
             it != this->drivers->end(); it++) {
            if (!(*it)->isInTrip()) {
                currentDistance = distanceOfDriverFromLocation(*it, location);
                if (distance == -1) {
                    distance = distanceOfDriverFromLocation((*it), location);
                    closest = *it;
                }
                if (distance > currentDistance) {
                    closest = *it;
                    distance = currentDistance;
                }
            }
        }
        if (distance != -1) {
            return closest;
        }
    }
    return NULL;
}

Value *TaxiCenter::driverLocation(Driver cabbie) {
    return cabbie.getLocation();
}

std::list<Element *> *TaxiCenter::createPath(Value *start, Value *end) {
    std::list<Element *> *path = this->bfs->pathDrive(start, end);
    return path;
}

void TaxiCenter::deleteTripFromList(Trip *t) {
    bool ifFind = false;
    for (std::list<Trip *>::iterator it = this->trip->begin(); it != this->trip->end(); it++) {
        if ((*it) == t) {
            ifFind = true;
            break;
        }
    }
    if (ifFind) {
        this->trip->remove(t);
        delete t;
    }
}

bool TaxiCenter::moveOneStep(int currentTime) {
    bool someoneMoved = false;
    for (std::list<Driver *>::iterator it = this->drivers->begin();
         it != this->drivers->end(); it++) {
        if ((*it)->isInTrip() && ((*it)->getCurrentTrip()->getStartTime() < currentTime)) {
            (*it)->move();
            someoneMoved = true;
            if (!(*it)->isInTrip()) {
                //  setRateOfDriver((*it), (*it)->getCurrentTrip().listPassenger());
                this->deleteTripFromList((*it)->getCurrentTrip());
            }
        }
    }
    return someoneMoved;
}

void TaxiCenter::setRateOfDriver(Driver *driver, std::list<Passenger *> *listPassenger) {
    double avarageRate = 0;
    for (std::list<Passenger *>::iterator passengerIt = listPassenger->begin();
         passengerIt != listPassenger->end(); passengerIt++) {
        avarageRate += (*passengerIt)->getRate();
    }
    driver->setRate(avarageRate / listPassenger->size(), listPassenger->size());
}

int TaxiCenter::numberOfDriver() {
    if (this->drivers == NULL) {
        return 0;
    } else {
        return this->drivers->size();
    }
}

int TaxiCenter::numberOfCabs() {
    if (this->cabs == NULL) {
        return 0;
    } else {
        return this->cabs->size();
    }
}

void TaxiCenter::addCab(Cab *cab) {
    this->cabs->push_back(cab);
}

double TaxiCenter::distanceOfDriverFromLocation(Driver *driver, Value *location) {
    double sizeOfPath;
    std::list<Element *> *path = this->bfs->pathDrive(driver->getLocation(), location);
    sizeOfPath = path->size();
    delete (path);
    return sizeOfPath;
}

int TaxiCenter::numberOfTrip() {
    return this->trip->size();
}

void TaxiCenter::addTrip(Trip *trip) {
    this->trip->push_back(trip);
}

Value *TaxiCenter::getDriverLocation(int driverID) {
    std::list<Driver *>::iterator it = this->drivers->begin();
    for (std::list<Driver *>::iterator it = this->drivers->begin();
         it != this->drivers->end(); it++) {
        if ((*it)->getID() == driverID) {
            return (*it)->getLocation();
        }
    }
    return NULL;
}

void TaxiCenter::addDriver(Driver *driver) {
    this->drivers->push_back(driver);
}

string TaxiCenter::connectDriverToTaxi(char *driver, char *end) {
    Driver *driverD;
    boost::iostreams::basic_array_source<char> device(driver, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> driverD;

    this->addDriver(driverD);
    for (std::list<Cab *>::iterator cab = this->cabs->begin();
         cab != this->cabs->end(); cab++) {
        if (driverD->getDriverCabID() == (*cab)->getID()) {
            driverD->setCab(*cab);
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(
                    inserter);
            boost::archive::binary_oarchive oa(s);
            oa << (*cab);
            s.flush();
            return serial_str;
        }
    }
    return "NULL";
}
