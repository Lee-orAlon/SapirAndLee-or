#ifndef EX3_MAINFLOW_H
#define EX3_MAINFLOW_H

#include "Grid.h"
#include "Driver.h"
#include "TaxiCenter.h"
#include "Clock.h"

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

    /*TODO- I've changed this function signature and did this function public (it was private before the changing)*/
    Driver *createDriver(char * driver);

    /*TODO- I've added this function- it returns the number of task.*/
    int  doUserRequest();
    /*TODO i've added this function*/
    int getCounter();
    /*TODO i've added this function*/
    int getNumberOfDrivers();
private:
    int task;
    /*TODO i've added this member*/
    int counter; //Count the number of times that the user wanted to do task 1.
    /*TODO i've added this member*/
    int numberOfDrivers;
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