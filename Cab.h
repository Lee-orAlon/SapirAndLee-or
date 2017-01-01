//
// Created by lee-or on 29/11/16.
//

#ifndef EX2_CAB_H
#define EX2_CAB_H

#include <string>

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
    // double kmPassed;
public:
    Cab(int id, char color,char manufacturer);
    Cab();
    ~Cab();
    double getTariff ();
    virtual double getPassedKm ()=0;
    int getID();
    virtual int move ()=0;
};
#endif //EX2_ADVANCEDPROGRAMMING1_CAB_H