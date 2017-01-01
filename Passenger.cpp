#include "Passenger.h"

Passenger::Passenger(Value *sorce, Value *destination) {
    this->source = sorce;
    this->destination = destination;
    this->rate = 0;

}

Passenger::Passenger() {
    //this->source=Point(1,2);
    //this->destination=Point(1,2);
}

Value *Passenger::getSource() {
    return this->source;
}

Value *Passenger::getDestination() {
    return this->destination;
}

double Passenger::getRate() {
    this->rate = rand() % 5 + 1;
    return this->rate;
}

Passenger::~Passenger() {
    delete this->source;
    delete this->destination;
}