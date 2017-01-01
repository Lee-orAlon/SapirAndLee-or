#ifndef EX2_TRIP_H
#define EX2_TRIP_H
#include "Value.h"
#include "Passenger.h"
#include <list>
/**
 * Trip class- a class of a single trip.
 */
class Trip {
private:
    int number; //ID number of this Trip.
    Value *start;
    Value* end;
    double metersPass;
    int numOfPassengers;
    std::list<Passenger*> *passengers;
    double tariff;
public:
    /**
     * constructor.
     * @param start start location.
     * @param end end location.
     * @param passengers passengers that are in this trip.
     * @param tariff the tariff of this Trip.
     */
    Trip(Value* start, Value* end, std::list<Passenger*> *passengers, double tariff);
    /**
     * Defualt constructor.
     * @return
     */
    Trip ();
    /**
     * Destructor.
     */
    ~Trip();
    std::list<Passenger*>*listPassenger();
    /*
     * return point start
     */
    Value *getStart();
    /*
     * return point end
     */
    Value *getEnd();
    /*
     * return tariff
     */
    double getTariff();
    /*
     * return mater passed
     */
    double getMeterPass();
    /*
     * return number of trip
     */
    int getNumOfTrip();
    /*
     * return number of passenger
     */
    int getNumOfPassengers();
    /*
     * set the meter that pass
     */
    void setPassedMeters(int pass);
    /*
     * comper between two trips
     */
    bool operator==(const Trip  &other)const;

    /*
     * constractor recive number of passenger instead of passenger
     */
    Trip(int id, Value* start, Value *end, int numberOfPassengers, double tariff);
};
#endif //EX2_ADVANCEDPROGRAMMING1_TRIP_H