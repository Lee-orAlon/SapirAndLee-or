#include <iostream>
#include "Trip.h"

Trip::Trip(Value *start, Value *end, std::list<Passenger *> *passengers, double tariff) {
    this->start = start;
    this->end = end;
    this->passengers = passengers;
    this->tariff = tariff;
    if (passengers != NULL)
        this->numOfPassengers = passengers->size();
    else
        this->numOfPassengers = 0;
    this->metersPass = -1;
}

Trip::Trip(int id, Value *start, Value *end, int numberOfPassengers, double tariff) {
    this->start = start;
    this->end = end;
    this->passengers = new std::list<Passenger *>;
    this->tariff = tariff;
    this->numOfPassengers = numberOfPassengers;
    this->metersPass = -1;
    this->numOfPassengers = numberOfPassengers;
    this->number = id;
}

Value *Trip::getStart() {
    return this->start;
}

Value *Trip::getEnd() {
    return this->end;
}

double Trip::getMeterPass() {
    return this->metersPass;
}

double Trip::getTariff() {
    return this->tariff;
}

int Trip::getNumOfTrip() {
    return this->number;
}

Trip::Trip() {}

int Trip::getNumOfPassengers() {
    return this->numOfPassengers;
}

void Trip::setPassedMeters(int pass) {
    this->metersPass += pass;
}

std::list<Passenger *> *Trip::listPassenger() {
    return this->passengers;
}

bool Trip::operator==(const Trip &other) const {
    //std::list<Passenger *>::iterator it = this->passengers->begin();
    if (this->numOfPassengers != other.numOfPassengers)
        return false;
    if (this->start != other.start)
        return false;
    if (this->end != other.end)
        return false;
    //This is not relevant for now (no passengers).
    /*  std::list<Passenger *>::iterator itThis=this->passengers->begin();
      for (std::list<Passenger *>::iterator it=other.passengers->begin()
              ;it != this->passengers->end(); it++) {
          if((*it)->getSorce()!=(*itThis)->getSource() ||
             (*it)->getDestination()!=(*itThis)->getDestination())
              return false;
          itThis++;
      }*/
    return true;
}

Trip::~Trip() {
    delete (this->start);
    delete (this->end);
    delete (this->passengers);
}