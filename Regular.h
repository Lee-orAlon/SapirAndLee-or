#ifndef EX2_REGULAR_H
#define EX2_REGULAR_H

#include "Cab.h"

/**
 * Regular class- a class of a Cab of type Regular.
 */
class Regular : public Cab {
private:
    int factor;
    double kmPassed;

    /**
     * setPassedKm- set the number of km that this Cab has passed.
     */
    void setPassedKm();

public:
    /**
    * Constructor.
    * @param id the ID of this Regular Cab.
    * @param color a char that represents the color of this Regular Cab.
    * @param manufacturer a char the represents the manufacturer of this Regular Cab.
    */
    Regular(int id, char color, char manufacturer);

    /**
     * move- this function manage the movments of this Regualr Cab.
     */
    int move();

    /*
     * getPassedKm- return the meter that this Regular Cab has passed.
     */
    double getPassedKm();

    /**
     * getTariff.
     * @return the tariff of this Reular Cab.
     */
    double getTariff();
};

#endif //EX2_ADVANCEDPROGRAMMING1_REGULAR_H