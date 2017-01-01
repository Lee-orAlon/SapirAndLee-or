#ifndef EX3_MAINFLOW_H
#define EX3_MAINFLOW_H

#include "Grid.h"
#include "Driver.h"
#include "TaxiCenter.h"

/*
 * MainFlow class- this class creates a Taxi Center and manage it.
 * It receive inputs from the user and manage the Taxi Center according to it.
 */
class MainFlow {
public:
    /**
     * Constructor.
     */
    MainFlow();

    /**
     * Destructo.
     */
    ~MainFlow();

private:
    TaxiCenter *taxiCenter;
    Map *map;

    /**
     * createMap.
     * @return a new Map (according to the user's input.
     */
    Map *createMap();

    /**
     * createDriver.
     * @return a new Driver (according to the user's input).
     */
    Driver *createDriver();

    Passenger *createPassenger();

    /**
     * createCab.
     * @return a new Cab (according to the user's input).
     */
    Cab *createCab();

    /**
     * createTrip.
     * @return a new Trip (according to the user's input).
     */
    Trip *createTrip();

    /**
     * printDriverLocation- print a driver's location (by the driver's ID).
     */
    void printDriverLocation();
};

#endif //EX3_MAINFLOW_H