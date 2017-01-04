#include "Luxury.h"
#include <boost/serialization/export.hpp>
Luxury::Luxury(int id, char color, char manufacturer) : Cab(id, color, manufacturer) {
    this->factor = 2;
}
void Luxury::setPassedKm() {
    this->kmPassed += this->factor;
}
int Luxury::move() {
    this->setPassedKm();
    return this->factor;
}
double Luxury::getPassedKm() {
    return this->kmPassed;
}
double Luxury::getTariff() {
    return this->factor;
}
Luxury::Luxury(){

}
BOOST_CLASS_EXPORT(Luxury);