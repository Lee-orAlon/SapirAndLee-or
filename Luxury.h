#ifndef EX2_LUXURY_H
#define EX2_LUXURY_H

#include "Cab.h"

/**
 * Luxury class- a class of a cab from type Luxury.
 */
class Luxury : public Cab {
private:
    int factor;
    double kmPassed;
    /**
     * setPassedKm- set the number of km that this Cab has passed.
     */
    void setPassedKm();
public:
    /**
     * constructor.
     * @param id the ID of this Luxury Cab.
     * @param color a char which represtents the color of this Luxury Cab.
     * @param manufacturer a char which represents the manufacturer of this Luxury Cab.
     */
    Luxury(int id, char color, char manufacturer);

    /**
     * move- this function manage the movments of this Luxury Cab.
     */
    int move();

    /*
     * getPassedKm- return the meter that this Luxury Cab has passed.
     */
    double getPassedKm();

    /*
     * getTariff- return the tariff of this Luxury Cab.
     */
    double getTariff();
};

#endif //EX2_ADVANCEDPROGRAMMING1_LUXURY_H