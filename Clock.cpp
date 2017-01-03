#include "Clock.h"
Clock::Clock() {
    this->time=0;
}

void Clock::increaseTimeByOne() {
    this->time++;
}

int Clock::getTime() {
    return this->time;
}

Clock::~Clock() {}