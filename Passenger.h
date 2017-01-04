#ifndef EX2_PASSENGER_H
#define EX2_PASSENGER_H

#include <cmath>
#include <cstdlib>
#include "Value.h"
#include "Point.h"
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
 * Passenger class- a class of a single Passenger.
 */
class Passenger {
private:
    Point *source;
    Point *destination;
    double rate;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & source;
        ar & destination;
        ar& rate;


    }
public:
    /**
     * Constructor.
     * @param sorce the source point of this Passenger.
     * @param destination the destination point of this Passenger.
     */
    Passenger(Point *sorce,Point *destination);

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