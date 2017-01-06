#ifndef EX2_TRIP_H
#define EX2_TRIP_H

#include "Value.h"
#include "Passenger.h"
#include <list>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

/**
 * Trip class- a class of a single trip.
 */
class Trip {
private:
    int number; //ID number of this Trip.
    Value *start;
    Value *end;
    double metersPass;
    int numOfPassengers;
    std::list<Passenger *> *passengers;
    double tariff;
    int startTime;
    bool hasDriver;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & number;
        ar & start;
        ar & end;
        ar & numOfPassengers;
        ar & tariff;
        ar & passengers;
        ar & metersPass;
        ar & startTime;
        ar & hasDriver;

    }

public:
    /**
     * constructor.
     * @param start start location.
     * @param end end location.
     * @param passengers passengers that are in this trip.
     * @param tariff the tariff of this Trip.
     * @param time the start time of the trip.
     */
    Trip(Value *start, Value *end, std::list<Passenger *> *passengers, double tariff, int time);

    /**
     * Defualt constructor.
     * @return
     */
    Trip();

    /**
     * Destructor.
     */
    ~Trip();

    std::list<Passenger *> *listPassenger();

    /**
     * getStart.
     * @return the start point (value) of this trip.
     */
    Value *getStart();

    /**
     * getEnd.
     * @return the end point (value) of this trip.
     */
    Value *getEnd();

    /**
     * getTariff.
     * @return the tariff of this trip.
     */
    double getTariff();

    /**
     * getMeterPass.
     * @return the number of meters that were passed.
     */
    double getMeterPass();

    /*
     * return number of trip
     */
    int getNumOfTrip();

    /*
     * return number of passenger in this trip.
     */
    int getNumOfPassengers();

    /*
     * set number of meters that have passed.
     */
    void setPassedMeters(int pass);

    /*
     * Override to eqaul operand.
     */
    bool operator==(const Trip &other) const;

    /**
     * Constructor.
     * @param id the ID of this trip.
     * @param start the start point (value) of this trip.
     * @param end the end point (value) of this trip.
     * @param numberOfPassengers the number of passenger that are in this trip.
     * @param tariff the tariff of this trip.
     * @param time the start time of this trip.
     * @return
     */
    Trip(int id, Value *start, Value *end, int numberOfPassengers, double tariff, int time);

    /**
     * getStartTime.
     * @return the start time of this trip.
     */
    int getStartTime();

    /**
     * doesTripHasDriver.
     * @return true if this trip has a driver that will implement it. Else, returns false.
     */
    bool doesTripHasDriver();

    /**
     * setTripHasDriverToBeTrue- set that this trip has a driver that will implements it.
     */
    void setTripHasDriverToBeTrue();
};

#endif //EX2_ADVANCEDPROGRAMMING1_TRIP_H