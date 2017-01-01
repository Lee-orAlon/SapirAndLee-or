#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

#include <cmath>
#include <cstdlib>
#include "Value.h"

/**
 * Passenger class- a class of a single Passenger.
 */
class Passenger {
private:
    Value *source;
    Value *destination;
    double rate;
public:
    /**
     * Constructor.
     * @param sorce the source point of this Passenger.
     * @param destination the destination point of this Passenger.
     */
    Passenger(Value *sorce, Value *destination);

    /**
     * Defualt constructor.
     */
    Passenger();

    /**
     * Destructor.
     */
    ~Passenger();

    /**
     * getSource.
     * @return th source point of this Passenger.
     */
    Value *getSource();

    /**
     * getDestination.
     * @return the destination point of this Passenger.
     */
    Value *getDestination();

    /**
     * getRate.
     * @return the rate of this Passenger about the Driver.
     */
    double getRate();
};

#endif //EX2_PASSENGER_H