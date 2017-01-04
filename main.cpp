/**
 * main- the main function.
 * @return 0
 */
#include "Driver.h"
#include "Point.h"
#include "BFS.h"
#include "TaxiCenter.h"
#include "Trip.h"
#include "Passenger.h"
#include <cstdlib>
#include "Regular.h"
#include "Luxury.h"
#include <iostream>
std::stringstream ss;
using namespace std;
//Driver(int id, int age, char status, int exp, int cabID);
int main(int argc, char**argv) {
   Driver *d=new Driver(12345,50,'s',12,123);
 d->addCabToDriver(new Regular(12,'B','H'));
    std::string serial_str;
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << d;
    s.flush();
    cout << serial_str << endl;

    Driver *newD;
   boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >>newD;

    cout << *newD;
    delete d;
    delete newD;
    return 0;
}

/*
GridPoint *gp = new GridPoint(new Point(1,5));

std::string serial_str;
boost::iostreams::back_insert_device<std::string> inserter(serial_str);
boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
boost::archive::binary_oarchive oa(s);
oa << gp;
s.flush();

cout << serial_str << endl;

GridPoint *gp2;
boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
boost::archive::binary_iarchive ia(s2);
ia >> gp2;

cout << *gp2;

delete gp;
delete gp2;
return 0;
/*
 *
10 10
2
 1,0
 3,3
2
1,0,0,3,3,2,50
3
123,2,H,G
1
123,55,5,3,123
1
12345,50,M,23,111
2
2,0,0,4,9,6,99
3
111,1,H,G
6
4
12345
 */
/*
 *
3 3
0
1
1,1,M,1,1
2
6,0,0,2,1,4,2.9
3
1,1,H,R
6
4
1
(2,1)
1
2,2,S,2,2
2
3,0,0,2,2,1,1.2
3
2,1,H,G
6
4
1
 */