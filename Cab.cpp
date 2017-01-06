#include "Cab.h"

Cab::Cab(int id, char color, char manufacturer) {
    if (color == 'B') {
        this->color = B;
    }
    if (color == 'G') {
        this->color = G;
    }
    if (color == 'P') {
        this->color = P;
    }
    if (color == 'R') {
        this->color = R;
    }
    if (color == 'W') {
        this->color = W;
    }
    if (manufacturer == 'F') {
        this->manufacturer = F;
    }
    if (color == 'H') {
        this->manufacturer = H;
    }
    if (color == 'S') {
        this->manufacturer = S;
    }
    if (color == 'T') {
        this->manufacturer = T;
    }
    this->id = id;
}

Cab::Cab() {
}

Cab::~Cab() {
}

double Cab::getTariff() {
    return this->tariff;
}

int Cab::getID() {
    return this->id;
}




