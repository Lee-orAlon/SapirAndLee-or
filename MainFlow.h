#ifndef EX3_MAINFLOW_H
#define EX3_MAINFLOW_H

#include "Grid.h"
#include "Driver.h"
#include "TaxiCenter.h"
#include "Clock.h"
#include "Udp.h"

/*
 * MainFlow class- this class creates a Taxi Center and manage it.
 * It receive inputs from the user and manage the Taxi Center according to it.
 */
class MainFlow {
public:
    /**
     * Constructor.
     */
    MainFlow(int port);

    /**
     * Destructor.
     */
    ~MainFlow();

private:
    bool isThereConnection;
    int task;
    Udp *udp;
    Clock clock;
    TaxiCenter *taxiCenter;
    Map *map;

    /**
     * createMap.
     * @return a new Map (according to the user's input.
     */
    Map *createMap();

    //This function is not relevant for this exercise.
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