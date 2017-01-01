#ifndef EX2_SQUARE_H
#define EX2_SQUARE_H

#include <iostream>
#include "Point.h"
#include "Element.h"

/**
 * Square class- this class represents a square in a 2D matrix.
 * This class extends the 'Element' class.
 */
class Square : public Element {
private:
    Value *leftNeighbor;
    Value *rightNeighbor;
    Value *upNeighbor;
    Value *downNeighbor;
    bool visited;
    Value *myLocation;
    enum Directions {
        leftDir = 1,
        upDir = 2,
        rightDir = 3,
        downDir = 4,
        notValid = 5
    };
    enum Directions fatherDirection;
public:
    /**
     * Defualt constructor.
     */
    Square();

    /**
     * Constructor
     * @param myself the point which represents the location of this Square in the matrix.
     */
    Square(Value *myself);

    /**
     * setLeftNeighbor.
     * @param left the left neighbor of this Square in the matrix.
     * This function links between a Square and its left neighbor.
     */
    void setLeftNeighbor(Value *left);

    /**
     * setRightNeighbor.
     * @param right the right neighbor of this Square in the matrix.
     * This function links between a Square and its right neighbor.
     */
    void setRightNeighbor(Value *right);

    /**
     * setUpNeighbor.
     * @param up the upper neighbor of this Square in the matrix.
     * This function links between a Square and its neighbor above.
     */
    void setUpNeighbor(Value *up);

    /**
     * setDownNeighbor.
     * @param down the neighbor that below this Square in the matrix.
     * This function links between a Square and its neighbor below.
     */
    void setDownNeighbor(Value *down);

    /**
     * getMyLocation
     * @return the location (coordinate) of this Square in the matrix.
     */
    Value *getMyLocation();

    /**
     * setVisit.
     * Mark that this Square as "been visited", means this Square has been passed.
     */
    void setVisit();

    /**
     * hasLeftNeighbor.
     * @return 'true' if this Square has a left neigbor in the matrix. Else, returns 'false'.
     */
    bool hasLeftNeighbor();

    /**
     * hasRightNeighbor.
     * @return 'true' if this Square has a right neigbor in the matrix. Else, returns 'false'.
     */
    bool hasRightNeighbor();

    /**
     * hasUpNeighbor.
     * @return 'true' if this Square has a neigbor above in the matrix. Else, returns 'false'.
     */
    bool hasUpNeighbor();

    /**
     * hasDownNeighbor.
     * @return 'true' if this Square has a neigbor below in the matrix. Else, returns 'false'.
     */
    bool hasDownNeighbor();

    /**
     * getLeftNeighbor.
     * @return the left neighbor of this Square in the matrix.
     * Note: If this Square doesn't have a left neighbor, then the returned value will be 'NULL'.
     */
    Value *getLeftNeighbor();

    /**
     * getRightNeighbor.
     * @return the right neighbor of this Square in the matrix.
     * Note: If this Square doesn't have a right neighbor, then the returned value will be 'NULL'.
     */
    Value *getRightNeighbor();

    /**
     * getUpNeighbor.
     * @return the neighbor above this Square in the matrix.
     * Note: If this Square doesn't have a neighbor above, then the returned value will be 'NULL'.
     */
    Value *getUpNeighbor();

    /**
     * getDownNeighbor.
     * @return the neighbor below this Square in the matrix.
     * Note: If this Square doesn't have a neighbor below, then the returned value will be 'NULL'.
     */
    Value *getDownNeighbor();

    /**
     * ifVisited.
     * @return 'true' if this Square has been visited (if this Square has been passed).
     *          Else, returns 'false'.
     */
    bool ifVisited();

    /**
     * setFatherDirection.
     * @param direction the direction of this Square's 'father' (the Square that is before this
     *                  Square in the path) relative to this Square.
     * This function links between a Square and its 'father'.
     */
    void setFatherDirection(int direction);

    /**
     * getFatherCoordinate.
     * @return this Square's father coordinate (Value) in the matrix.
     */
    Value *getFatherCoordinate();

    /**
     * Destructor.
     */
    ~Square();

    /**
     * hasFatherDirection.
     * @return 'true' if this Square has a valid father direction. Else, returns 'false'.
     */
    bool hasFatherDirection();

    /**
     * setUnvisited- set this Square to be marked as not-visit.
     */
    void setUnvisited();
};

#endif //TRY_SQUARE_H