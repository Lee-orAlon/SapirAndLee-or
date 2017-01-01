#include "Regular.h"

Regular::Regular(int id, char color, char manufacturer) : Cab(id, color, manufacturer) {
    this->factor = 1;
}

void Regular::setPassedKm() {
    this->kmPassed += this->factor;
}

int Regular::move() {
    this->setPassedKm();
    return this->factor;
}

double Regular::getPassedKm() {
    return this->kmPassed;
}

double Regular::getTariff() {
    return this->factor;
}