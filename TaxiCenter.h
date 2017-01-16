#ifndef EX2_TAXICENTER_H
#define EX2_TAXICENTER_H

#include <list>
#include "Driver.h"
#include "Map.h"
#include "Trip.h"
#include "BFS.h"
#include "Value.h"
#include <queue>
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
#include <boost/serialization/base_object.hpp>
#include <pthread.h>

using namespace std;

/**
 * TaxiCenter- a class of a single taxi center.
 */
class TaxiCenter {
private:
    std::list<Driver *> *drivers;
    std::list<Cab *> *cabs;
    std::list<Trip *> *trip;
    Grid *grid;
    BFS *bfs;
    /*TODO*/
    pthread_mutex_t connection_locker;
    //This function is not relevant for this exercise.
    void setRateOfDriver(Driver *driver, std::list<Passenger *> *listPassenger);

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & grid;
        ar & bfs;
    }

public:
    /**
     * constructor.
     * @param grid the Map of the world which the taxi center lives in.
     * @param bfs a variable of type BFS algorithm.
     */
    TaxiCenter(Grid *grid, BFS *bfs);

    /*
     * destructor.
     */
    ~TaxiCenter();

    /**
     * constructor.
     */
    TaxiCenter();

    /**
     * listOfTrip.
     * @return a list of the trips that are taking action at this moment.
     */
    std::list<Trip *> *listOfTrip();

    /**
     * listOfDriver.
     * @return a list of all the drivers that works in this Taxi Center.
     */
    std::list<Driver *> *listOfDriver();

    /**
     * createTrip.
     * @param start start point of the trip.
     * @param end end point of the trip.
     * @param p a list of the Passenger(s) that are in this Trip.
     * @param tariff the tariff of this trip;
     */
    void createTrip(Trip *t);

    /**
     * findClosestDriver.
     * @param location the location which the user wants to know who is the closest Driver to it.
     * @return a pointer to the closest Driver to this 'location'.
     */
    Driver *findClosestDriver(Value *location);

    /**
     * driverLocation.
     * @param cabbie the Driver which te user wants to know its location.
     * @return the location of the Driver.
     */
    Value *driverLocation(Driver cabbie);

    /**
     * createPath.
     * @param start start point of this path.
     * @param end end point of this path.
     * @return the minimal path between 'start' and 'end'.
     */
    std::list<Element *> *createPath(Value *start, Value *end);

    /**
     * deleteTripFromList.
     * @param t the Trip which the user wants to delete.
     */
    void deleteTripFromList(Trip *t);

    /**
     * numberOfDriver.
     * @return the number of Drivers that are in this Taxi Center.
     */
    int numberOfDriver();

    /**
     * numberOfCabs.
     * @return the number of Cabs that are in this Taxi Center.
     */
    int numberOfCabs();

    /**
     * addDriver.
     * @param driver the Driver which the user wants to add to this Taxi Center.
     */
    void addDriver(Driver *driver);

    /**
     * addCab.
     * @param cab the Cab which the user wants to add to this Taxi Center.
     */
    void addCab(Cab *cab);

    /**
     * distanceOfDriverFromLocation.
     * @param driver the driver which the user wants to know its distance from a given location.
     * @param location the location which the user wants to know its distance from a given driver.
     * @return the distance betwwen the given driver to the given location.
     */
    double distanceOfDriverFromLocation(Driver *driver, Value *location);

    /*
     * this function recive trup and add it to taxiCenetr
     */
    void addTrip(Trip *trip);

    /**
     * getDriverLocation.
     * @param driverID the ID of the driver which the user wants to know its location.
     * @return the location of the driver.
     */
    Value *getDriverLocation(int driverID);

    /**
     * connectDriverToTaxi- this function give to all driver taxi according to driver id
     * @param driver the begining of the buffer which holds the driver's serialized information.
     * @param end the end of the buffer which holds the driver's serialized information.
     * @return the srialized cab of the driver.
     */
    string connectDriverToTaxi(char *driver, char *end);

    /*TODO*/
    bool moveOneStep(int , int ID);

    /**
     * numberOfTrip.
     * @return the number of trips that are in this Taxi Center at this moment.
     */
    int numberOfTrip();

    /**
     * connectDriverToTrip- give driver a trip according to its location.
     * @param currentTime
     */
    Trip *connectDriverToTrip(int currentTime);

    /**
     * serializePath.
     * @param currentTime the current time of the world.
     * @return the serialized path of the trip.
     */
    string serializePath(int currentTime);

    /*TODO*/
    int getIDFromSerialization(char *driver);
};

#endif //EX2_TEXICENTER_H