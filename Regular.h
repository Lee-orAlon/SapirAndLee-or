#ifndef EX2_REGULAR_H
#define EX2_REGULAR_H
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
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &factor;
        ar &kmPassed;
        ar& boost::serialization::base_object<Cab>(*this);
    }
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
    Regular();
};


#endif //EX2_ADVANCEDPROGRAMMING1_REGULAR_H