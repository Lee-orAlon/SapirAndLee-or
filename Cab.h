#ifndef EX2_CAB_H
#define EX2_CAB_H

#include <string>
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

class Cab {
private:
    /*
     * 1- Red
     * 2- Blue
     * 3- Green
     * 4- Pink
     * 5- White
     */
    enum Color {
        R = 1,
        B = 2,
        G = 3,
        P = 4,
        W = 5
    };
    /*
     * 1- Honda
     * 2- Subaro
     * 3- Tesla
     * 4- Fiat
     */
    enum Manufacturer {
        H = 1,
        S = 2,
        T = 3,
        F = 4
    };
    //id of cab
    int id;
    //color
    Color color;
    //manufacturer of cab
    Manufacturer manufacturer;
    double tariff;
    double kmPassed;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & id;
        ar & color;
        ar & manufacturer;
    }

public:
    /**
     * Constructor.
     * @param id the ID of the cab.
     * @param color the color of the cab.
     * @param manufacturer the manufacturer of the cab.
     */
    Cab(int id, char color, char manufacturer);

    /**
     * Constructor.
     */
    Cab();

    /**
     * Destructor.
     */
    ~Cab();

    /**
     * getTariff.
     * @return the tariff of this cab.
     */
    double getTariff();

    /**
     * getPassedKm.
     * @return the number of km that this cab has passed.
     */
    virtual double getPassedKm()=0;

    /**
     * getID.
     * @return the ID of this cab.
     */
    int getID();

    /**
     * move- this function manages the movments of this Cab.
     */
    virtual int move()=0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab)
#endif //EX2_ADVANCEDPROGRAMMING1_CAB_H