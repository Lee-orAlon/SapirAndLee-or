#include <iostream>
#include "Point.h"
#include <boost/serialization/export.hpp>

Point::Point(int xValue, int yValue) {
    this->x = xValue;
    this->y = yValue;
}

int Point::getX() {
    return this->x;
}

Point::Point() {
}

int Point::getY() {
    return this->y;
}

void Point::printValue() {
    std::cout << "(" << this->getX() << "," << this->getY() << ")" << std::endl;
}

int Point::getiValue(int i) {
    switch (i) {
        case 1:
            return this->x;
            break;
        case 2:
            return this->y;
            break;
    }
}

bool Point::operator==(const Point &other) const {
    return this->x == other.x && other.y == this->y;
}

bool Point::operator!=(const Point &other) const {
    return this->x != other.x || other.y == this->y;
}

Point::~Point() {
}

BOOST_CLASS_EXPORT(Point);