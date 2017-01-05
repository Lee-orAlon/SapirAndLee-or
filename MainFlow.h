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

    /*TODO- I've changed this function signature and did this function public (it was private before the changing)*/
    Driver *createDriver(char * driver);

    /*TODO- I've added this function- it returns the number of task.*/
    int  doUserRequest();
private:
    int task;
    Udp *udp;
    /*TODO I've removed the member counter and the member numberOfDrivers*/
    /*TODO i've added this member*/
    bool addDrivers;
    /*TODO i've added this member*/
    Clock clock;
    TaxiCenter *taxiCenter;
    Map *map;

    /**
     * createMap.
     * @return a new Map (according to the user's input.
     */
    Map *createMap();



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