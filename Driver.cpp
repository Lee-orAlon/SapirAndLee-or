#include <iostream>
#include "Driver.h"
#include "Point.h"

Driver::Driver(int id, int age, char status, Cab *cab, Value *currentLocation, int experience) {
    this->id = id;
    this->age = age;
    if (status == 'D') {
        this->status = D;
    }
    if (status == 'M') {
        this->status = M;
    }
    if (status == 'S') {
        this->status = S;
    }
    if (status == 'W') {
        this->status = W;
    }
    this->taxi = cab;
    this->path = NULL;
    this->inTrip = false;
    this->rate = 0;
    this->location = currentLocation;
    this->taxiID = cab->getID();
    this->experience = experience;
    this->numberOfRate = 0;
}

double Driver::getAverage() {
    return this->rate;
}

int Driver::getExperience() {
    return this->experience;
}

int Driver::getID() {
    return this->id;
}

bool Driver::isInTrip() {
    return this->inTrip;
}

Trip *Driver::getCurrentTrip() {
    return this->drive;
}

void Driver::enterPath(char *path, char *end) {
    std::list<Element *> *listElm;
    boost::iostreams::basic_array_source<char> device(path, end);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> listElm;
    this->path = listElm;
    this->setInTrip(true);
}

void Driver::setTrip(Trip *givenTrip) {
    this->drive = givenTrip;
    this->setInTrip(true);
}

Cab *Driver::getCab() {
    return this->taxi;
}

std::list<Element *> *Driver::getPath() {
    return this->path;
}

Value *Driver::getLocation() {
    return this->location;
}

bool Driver::isThereNextStep() {
    if (this->path != NULL) {
        if (this->path->empty()) {
            return false;
        } else {
            return true;
        }
    } else {
        return false;
    }
}

void Driver::move() {
    int numOfSteps;
    if (isThereNextStep()) {
        numOfSteps = this->taxi->move();
        this->drive->setPassedMeters(numOfSteps);
        for (int i = 0; i < numOfSteps; i++) {
            if (isThereNextStep()) {
                this->location = new Point((*this->path->begin())->getMyLocation()->getiValue(1),
                                           (*this->path->begin())->getMyLocation()->getiValue(2));
                this->path->remove(*this->path->begin());
            } else {
                delete (this->path);
                this->path = NULL;
                this->setInTrip(false);
                break;
            }
        }
    } else {
        delete (this->path);
        this->path = NULL;
        this->setInTrip(false);
    }
}

void Driver::setRate(double numberRateThisDrive, int numberOfPeople) {
    this->rate = (this->rate * this->numberOfRate + numberRateThisDrive * numberOfPeople) /
                 (this->numberOfRate + numberOfPeople);
    this->numberOfRate += numberOfPeople;
}

void Driver::setInTrip(bool drive) {
    this->inTrip = drive;
}

Driver::~Driver() {
    delete (this->location);
    //  this->taxi = NULL;
    // delete(this->taxi);
    // this->path = NULL;
    //  delete(this->path);
    //  this->drive = NULL;
    //  delete(this->drive);
}

Driver::Driver(int id, int age, char status, int exp, int cabID) {
    this->id = id;
    this->age = age;
    if (status == 'D') {
        this->status = D;
    }
    if (status == 'M') {
        this->status = M;
    }
    if (status == 'S') {
        this->status = S;
    }
    if (status == 'W') {
        this->status = W;
    }
    this->experience = exp;
    this->location = new Point(0, 0);
    this->taxiID = cabID;
    this->taxi = NULL;
    this->path = NULL;
}

Driver::Driver() {

}

int Driver::getDriverCabID() {
    return this->taxiID;
}

std::ostream &operator<<(std::ostream &os, const Driver &p) {
    os << '(' << p.id << ',' << p.age << ',' << p.status << ',' << p.experience << ',' << p.taxiID
       << ',' << p.location->getiValue(1) << ',' << ')';
    return os;
}

bool Driver::operator==(const Driver &other) const {
    //std::list<Passenger *>::iterator it = this->passengers->begin();
    if (this->id == other.id)
        return true;
    return false;
}

void Driver::setPath(std::list<Element *> *p) {
    this->path = p;
}

void Driver::setCab(Cab *cab) {
    this->taxi = cab;
}

void Driver::doNextMove() {
    int numOfSteps;
    if (isThereNextStep()) {
        numOfSteps = this->taxi->move();
        for (int i = 0; i < numOfSteps; i++) {
            if (isThereNextStep()) {
                this->location = (*this->path->begin())->getMyLocation();
                this->path->remove(*this->path->begin());
            } else {
                delete (this->path);
                this->path = NULL;
                this->setInTrip(false);
                break;
            }
        }
    } else {
        delete (this->path);
        this->path = NULL;
        this->setInTrip(false);
    }
}

Cab *Driver::deserializeCab(char *cab, char *end) {
    if (cab != "NULL") {
        Cab *newCab;
        boost::iostreams::basic_array_source<char> device(cab, end);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> newCab;
        return newCab;
    }
}


/*TODO*/
void Driver::setLocation(Value *loc) {
    this->location = loc;
}

/*TODO*/
string Driver::serializeMyLocation() {
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << this->location;
    s.flush();

    return serial_str;
}