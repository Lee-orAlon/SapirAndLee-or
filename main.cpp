#include "Point.h"
#include "BFS.h"
#include "MainFlow.h"
#include <cstdlib>
/*
using namespace std;

/*
/**
 * main- the main function.
 * @return 0
 */

#include "Point.h"
#include "BFS.h"
#include "TaxiCenter.h"
#include "Trip.h"
#include "Passenger.h"
#include <cstdlib>
#include "Regular.h"
#include "Luxury.h"
#include "Driver.h"
#include <iostream>
using namespace std;
#include <iostream>
//#include "gtest/gtest.h"

int main(int argc, char**argv) {

    // ::testing::InitGoogleTest(&argc, argv);
    // RUN_ALL_TESTS();
    MainFlow *mainFlow= new MainFlow();
    delete mainFlow;

    return 0;
}
/*int main() {
//function that get  input and enter into values
    MainFlow *mainFlow= new MainFlow();
    delete mainFlow;

    return 0;
}
*/

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