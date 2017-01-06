#include <iostream>
#include "MainFlow.h"

using namespace std;

/**
 * the main method of server.
 * @param argc number of argments that the user gives.
 * @param argv argv[1] accpected to be the port that the server listen to.
 */
int main(int argc, char **argv) {
    if (argc == 2) {
        MainFlow mainFLow(atoi(argv[1]));
    }
    return 0;
}