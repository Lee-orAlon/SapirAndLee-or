//
// Created by lee-or on 29/11/16.
//
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
     * 1-red
     * 2-blue
     * 3-green
     * 4-pink
     * 5-
     */
    enum Color{
        R = 1,
        B = 2,
        G = 3,
        P = 4,
        W = 5
    };
    /*
     * 1-honda
     * 2-subaro
     * 3-
     * 4-fiat
     */
    enum Manufacturer{
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
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &id;
        ar & color;
        ar& manufacturer;
    }
public:
    Cab(int id, char color,char manufacturer);
    Cab();
    ~Cab();
    double getTariff ();
    virtual double getPassedKm ()=0;
    int getID();
    virtual int move ()=0;
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Cab)
#endif //EX2_ADVANCEDPROGRAMMING1_CAB_H