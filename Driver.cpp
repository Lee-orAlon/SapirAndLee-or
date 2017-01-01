#include <iostream>
#include "Driver.h"
#include "Point.h"
#include <sys/socket.h>


Driver::Driver(int id, int age, char status, Cab *cab, Value *currentLocation, int experience) {
    this->id = id;
    this->age = age;

    if(status=='D'){
        this->status= D;
    }
    if(status=='M'){
        this->status = M;
    }
    if(status=='S'){
        this->status = S;
    }
    if(status=='W'){
        this->status = W;
    }
    this->taxi = cab;
    this->path = NULL;
    this->inTrip = false;
    this->rate = 0;
    this->location = currentLocation;
    this->taxiID = cab->getID();
    this->experience=experience;
    this->numberOfRate=0;
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

void Driver::setTrip(Trip *givenTrip, std::list<Element *> *givenPath) {
    if (givenPath != NULL) {
        this->drive = givenTrip;
        this->path = givenPath;
        this->setInTrip(true);
    }
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
    if(this->path!=NULL) {
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
        numOfSteps=this->taxi->move();
        this->drive->setPassedMeters(numOfSteps);
        for(int i=0; i<numOfSteps; i++) {
            if (isThereNextStep()) {
                this->location = (*this->path->begin())->getMyLocation();
                this->path->remove(*this->path->begin());
            } else {
                delete(this->path);
                this->path=NULL;
                this->setInTrip(false);
                break;
            }
        }
    } else {
        delete(this->path);
        this->path = NULL;
        this->setInTrip(false);
    }
}

void Driver::setRate(double numberRateThisDrive,int numberOfPeople){
    this->rate= (this->rate*this->numberOfRate+numberRateThisDrive*numberOfPeople)/
                ( this->numberOfRate+numberOfPeople);
    this->numberOfRate+=numberOfPeople;
}

void Driver::setInTrip(bool drive) {
    this->inTrip = drive;
}

Driver::~Driver() {
    delete(this->location);
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
    if(status=='D'){
        this->status= D;
    }
    if(status=='M'){
        this->status = M;
    }
    if(status=='S'){
        this->status = S;
    }
    if(status=='W'){
        this->status = W;
    }
    this->experience = exp;
    this->location = new Point(0,0);
    this->taxiID = cabID;
    this->taxi= NULL;
    this->path= NULL;
}

void Driver::addCabToDriver(Cab *cab) {
    this->taxi = cab;
}

int Driver::getDriverCabID() {
    return this->taxiID;
}

/**TODO*/
void Driver::connectToTaxiCenter() {
   // int s=socket()
}