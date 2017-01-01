
#ifndef EX2_DRIVER_H
#define EX2_DRIVER_H
#include <queue>
#include "Trip.h"
#include "Cab.h"
#include "Value.h"
#include "Element.h"
/**
 * Driver class- a class of a single driver.
 */
class Driver {
private:
    int numberOfRate;
    int id;
    int age;
    std::list<Element *> *path;
    enum Status {
        S = 1,
        M = 2,
        D = 3,
        W = 4
    };
    Status status;
    int experience;
    int average;
    Cab *taxi;
    bool inTrip;
    Trip *drive;
    Value* location;
    double rate;
    int taxiID;

    /**
     * setInTrip- set if the Driver's is in trip or not.
     * @param drive 'true' if the driver is in trip. Else, 'false'.
     */
    void setInTrip(bool drive);

    /**
     * isThereNextStep.
     * @return 'true' if the next step is not 'NULL'. Else, returns 'false'.
     */
    bool isThereNextStep();

public:
    /**
     * constructor.
     * @param id the ID of this Driver.
     * @param age the age of this Driver.
     * @param status the family status of this Driver.
     * @param cab the taxi of this Driver.
     * @param currentLocation the current location of this Driver.
     */
    /*TODO I'echanged this constructor (char insteadof int)*/
    Driver(int id, int age, char status, Cab *cab, Value* currentLocation,int experience);

    /**
     * Destructor.
     */
    ~Driver();

    /**
     * getAverage.
     * @return the average of sastification of ths Driver.
     */
    double getAverage();

    /**
     * getExperience.
     * @return return the years of experience of this Driver.
     */
    int getExperience();

    /**
     * getLocation.
     * @return the current location of this Driver.
     */
    Value *getLocation();

    /**
     * getID.
     * @return the ID of this Driver.
     */
    int getID();

    /**
     * isInTrip.
     * @return 'true' if this Driver is in Trip. Otherwise, returns 'false'.
     */
    bool isInTrip();

    /**
     * setTrip- set this Driver's trip.
     * @param givenTrip the Trip of this Driver.
     * @param givenPath the path which this driver should drive.
     */
    void setTrip(Trip *givenTrip, std::list<Element *> *givenPath);

    /**
     * getCab.
     * @return the Cab of this Driver.
     */
    Cab *getCab();

    /**
     * move- this function checkes the next move of the driver and act according to it.
     */
    void move();

    /**
    * constructor
    * @param source int id, int age, char status, int exp, int cabID)
    * @param  return
            * This function it constructor
    */
    Driver(int id, int age, char status, int exp, int cabID);
/**
    * constructor
    * @param source this function recuve cab
    * @param  return
            * add the cab to the drive
    */
    void addCabToDriver(Cab *cab);
    /**
    * getDriverCabID
    * @param source
    * @param  return
            * get the id of cab
    */
    int getDriverCabID();

    /**
      * constructor
      * @param source
      * @param  return
              * get the  cuu=rrent trip
      */
    Trip *getCurrentTrip();

    /**
      * setrate
      * @param source number of new rater ,new rate
      * @param  the function update the rate of the driver

      */
    void setRate(double numberRateThisDrive,int numberOfPeople);

    /**
      * constructor
      * @param source
      * @param  return
              * get the  cuu=rrent trip
      */
    std::list<Element*>*getPath();

    /**TODO*/
    void connectToTaxiCenter();
};

#endif //EX2_ADVANCEDPROGRAMMING1_DRIVER_H