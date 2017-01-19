#ifndef EX3_MAINFLOW_H
#define EX3_MAINFLOW_H

#include "Grid.h"
#include "Driver.h"
#include "TaxiCenter.h"
#include "Clock.h"
#include "Tcp.h"
#include "Client.h"
#include <pthread.h>
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

    /*TODO*/
    int getTask();

private:
    struct clientInfo{
        int clientSocket;
        int clientID;
        MainFlow *mainFlow;
        TaxiCenter *center;
    };
    bool isThereConnection;
    int task;
    Tcp *tcp;
    Clock clock;
    TaxiCenter *taxiCenter;
    Map *map;
    std::list<clientInfo *> *clients;

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


    /*TODO*/
    void addThreadsAndClients();

    /*TODO*/
    static void *case9(void *information);

    /*TODO*/
    void* switchCase();
};

#endif //EX3_MAINFLOW_H