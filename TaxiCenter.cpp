#include "TaxiCenter.h"
#include <boost/log/trivial.hpp>
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
  /* BOOST_LOG_TRIVIAL(debug) << "delete driver" <<endl;
    Driver *driver;
    std::list<Driver *>::iterator it = this->drivers->begin();
    while(this->drivers->size()>0){
        this->drivers->remove((*it));
        delete (*it);
        it++;
    }
    BOOST_LOG_TRIVIAL(debug) << "delete taxi" <<endl;
    std::list<Cab *>::iterator itCab = this->cabs->begin();
    while(this->cabs->size()>0){
        this->cabs->remove((*itCab));
        delete (*itCab);
        itCab++;
        BOOST_LOG_TRIVIAL(debug) << "delete taxi" <<endl;
    }
    BOOST_LOG_TRIVIAL(debug) << "delete trip" <<endl;
    std::list<Trip *>::iterator itTrip = this->trip->begin();
    while(this->trip->size()>0){
        this->trip->remove((*itTrip));
        delete (*itTrip);
        itTrip++;
    }
    delete this->drivers;
    delete (this->cabs);
    delete (this->trip);
    delete (this->grid);
    delete this->bfs;
    BOOST_LOG_TRIVIAL(debug) << "delete taxi center" <<endl;*/
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
    BOOST_LOG_TRIVIAL(debug) << "connect trips" <<this->trip->size()<< endl;
    std::list<Trip *>::iterator it = this->trip->begin();

    for (std::list<Trip *>::iterator it = this->trip->begin();
         it != this->trip->end(); it++) {
        if (((*it)->getStartTime() >= currntTime) && ((*it)->doesTripHasDriver() == false)) {
            if(currntTime==6)
                BOOST_LOG_TRIVIAL(debug) << "trip" <<(*it)->getTariff()<< endl;
            Driver *d = this->findClosestDriver((*it)->getStart());
            if (d != NULL) {
                /* TODO*/
              //  pthread_mutex_lock(&this->connection_locker);
                (*it)->setTripHasDriverToBeTrue();
                d->setTrip(*it);

                std::list<Element *> *pathD = this->bfs->pathDrive((*it)->getStart(),
                                                                   (*it)->getEnd());
                pathD->remove(*pathD->begin());
                d->setPath(pathD);
                (*it)->setTripHasDriverToBeTrue();
                /* TODO*/
               // pthread_mutex_unlock(&this->connection_locker);
                return (*it);
            }
        }
    }
    return NULL;
}

string TaxiCenter::serializePath(int currentTime) {
    pthread_mutex_lock(&this->connection_locker);
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
        pthread_mutex_unlock(&this->connection_locker);
        return serial_str;
    }
    pthread_mutex_unlock(&this->connection_locker);
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
                //print here
                if((*it)->getID()==0)
                BOOST_LOG_TRIVIAL(debug) << "driver 0 not in trip"<<std::endl;
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
   // BOOST_LOG_TRIVIAL(debug) << "number of trips before delete"<<this->trip->size()<<std::endl;
    pthread_mutex_lock(&this->connection_locker);
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
    pthread_mutex_unlock(&this->connection_locker);
   // BOOST_LOG_TRIVIAL(debug) << "number of trips afer delete"<<this->trip->size()<<std::endl;
}

bool TaxiCenter::moveOneStep(int currentTime, int ID) {
    bool someoneMoved = false;
    for (std::list<Driver *>::iterator it = this->drivers->begin();
         it != this->drivers->end(); it++) {
        if((*it)->getID() == ID) {
            if ((*it)->isInTrip() && ((*it)->getCurrentTrip()->getStartTime() < currentTime)) {
                (*it)->move();
                someoneMoved = true;
                if (!(*it)->isInTrip()) {
                 //   BOOST_LOG_TRIVIAL(debug) << "need delete"<< (*it)->getID()<<std::endl;
                    //BOOST_LOG_TRIVIAL(debug) << "before delete trip"<<this->trip->size()<<std::endl;
                    //  setRateOfDriver((*it), (*it)->getCurrentTrip().listPassenger());
                    this->deleteTripFromList((*it)->getCurrentTrip());
                    //BOOST_LOG_TRIVIAL(debug) << "after delete trip"<<this->trip->size()<<std::endl;
                }
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
    Driver *d;
    boost::iostreams::basic_array_source<char> device(driver, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> d;

    this->addDriver(d);
    for (std::list<Cab *>::iterator cab = this->cabs->begin();
         cab != this->cabs->end(); cab++) {
        if (d->getDriverCabID() == (*cab)->getID()) {
            d->setCab(*cab);
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

int TaxiCenter::getIDFromSerialization(char *driver, char *end) {
    Driver *d;
    boost::iostreams::basic_array_source<char> device(driver,end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> d;

    return d->getID();
}

/*TODO*/
string TaxiCenter::getCurrentLocationAndSerializeIt(int ID) {
    std::list<Driver *>::iterator it = this->drivers->begin();
    for (std::list<Driver *>::iterator it = this->drivers->begin();
         it != this->drivers->end(); it++) {
        if ((*it)->getID() == ID) {
            Value* loc = (*it)->getLocation();
            BOOST_LOG_TRIVIAL(debug) << "loc: " << loc->getiValue(1) << " , " << loc->getiValue(2) << endl;
            std::string serial_str;
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(
                    inserter);
            boost::archive::binary_oarchive oa(s);
            oa <<(loc);
            s.flush();
            return serial_str;
        }
    }

    return "NULL";
}
