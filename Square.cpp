#include <iostream>
#include "Square.h"

Square::Square() {
    this->myLocation = new Point(0, 0);
    this->downNeighbor = NULL;
    this->leftNeighbor = NULL;
    this->rightNeighbor = NULL;
    this->upNeighbor = NULL;
    this->fatherDirection = notValid;
    this->visited = false;
}

Square::Square(Value *myself) {
    this->myLocation = myself;
    this->downNeighbor = NULL;
    this->leftNeighbor = NULL;
    this->rightNeighbor = NULL;
    this->upNeighbor = NULL;
    this->fatherDirection = leftDir;
    this->visited = false;
}

Value *Square::getMyLocation() {
    return this->myLocation;
}

void Square::setLeftNeighbor(Value *left) {
    this->leftNeighbor = left;
}

void Square::setRightNeighbor(Value *right) {
    this->rightNeighbor = right;
}

void Square::setUpNeighbor(Value *up) {
    this->upNeighbor = up;
}

void Square::setDownNeighbor(Value *down) {
    this->downNeighbor = down;
}

void Square::setVisit() {
    this->visited = true;
}

bool Square::hasLeftNeighbor() {
    if (this->leftNeighbor == NULL)
        return false;
    else
        return true;
}

bool Square::hasRightNeighbor() {
    if (this->rightNeighbor == NULL)
        return false;
    else
        return true;
}

bool Square::hasUpNeighbor() {
    if (this->upNeighbor == NULL)
        return false;
    else
        return true;
}

bool Square::hasDownNeighbor() {
    if (this->downNeighbor == NULL)
        return false;
    else
        return true;
}

Value *Square::getLeftNeighbor() {
    return this->leftNeighbor;
}

Value *Square::getRightNeighbor() {
    return this->rightNeighbor;
}

Value *Square::getUpNeighbor() {
    return this->upNeighbor;
}

Value *Square::getDownNeighbor() {
    return this->downNeighbor;
}

bool Square::ifVisited() {
    return this->visited;
}

void Square::setFatherDirection(int direction) {
    switch (direction) {
        case 1:
            this->fatherDirection = leftDir;
            break;
        case 2:
            this->fatherDirection = upDir;
            break;
        case 3:
            this->fatherDirection = rightDir;
            break;
        case 4:
            this->fatherDirection = downDir;
            break;
        default:
            this->fatherDirection = notValid;
    }
}

Value *Square::getFatherCoordinate() {
    switch ((int) this->fatherDirection) {
        case 1:
            return getRightNeighbor();
            break;
        case 2:
            return getDownNeighbor();
            break;
        case 3:
            return getLeftNeighbor();
            break;
        case 4:
            return getUpNeighbor();
            break;
    }
}

Square::~Square() {
    delete (this->myLocation);
    delete (this->leftNeighbor);
    delete (this->upNeighbor);
    delete (this->rightNeighbor);
    delete (this->downNeighbor);
}

bool Square::hasFatherDirection() {
    if (this->fatherDirection != notValid)
        return true;
    else
        return false;
}

void Square::setUnvisited() {
    this->visited = false;
}
BOOST_CLASS_EXPORT(Square);