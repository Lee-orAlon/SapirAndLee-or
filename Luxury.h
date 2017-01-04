#ifndef EX2_LUXURY_H
#define EX2_LUXURY_H
#include "Cab.h"
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
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
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
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &factor;
        ar & kmPassed;
        ar& boost::serialization::base_object<Cab>(*this);
    }
public:
    /**
     * constructor.
     * @param id the ID of this Luxury Cab.
     * @param color a char which represtents the color of this Luxury Cab.
     * @param manufacturer a char which represents the manufacturer of this Luxury Cab.
     */
    Luxury(int id, char color, char manufacturer);
    Luxury();

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