#ifndef EX2_MATRIX_H
#define EX2_MATRIX_H

#include "Grid.h"
#include "Square.h"

/**
 * Matrix class- this class represents a 2D matrix. This class extens the 'Grid' class.
 */
class Matrix : public Grid {
private:
    int xSize;
    int ySize;
    Square ***matrix;
public:
    /**
     * Constructor.
     * @param x the size of the x axis (the number of coloumns of this Matrix).
     * @param y the size of the y axis (the number of rows of this Matrix).
     */
    Matrix(int x, int y);

    /**
     * compareVectors.
     * @param p1 a vector which will be compared to 'p2'.
     * @param p2 a vector which will be compared to 'p1'.
     * @return 'true' if p1 equals to p2. Else, returns 'false'.
     * Note: This comparison is based on the values of the parameters in the vectors (not whether
     *       these vectors have the same address).
     */
    bool compareVectors(Value *p1, Value *p2);

    /**
     * getMyCoordinate
     * @param s an Element in this Matrix.
     * @return the coordinate (Value) of the given Element on this Matrix.
     */
    Value *getMyCoordinate(Element *s);

    /**
     * getSquare
     * @param p a Value (coordinate) in this Matrix.
     * @return the Element (Square) which the given Value is its coordinate in this Matrix.
     */
    Element *getSquare(Value *p);

    /**
     * setVisitSquare.
     * @param p a Value in this Matrix that has been visited.
     * This function marks the Square of the given Value as visited.
     */
    void setVisitSquare(Value *p);

    /**
     * isVisited.
     * @param p a Value of a Square in this Mqtrix.
     * @return 'true' if the Square of the given Value has been visited. Else, returns 'false'.
     */
    bool isVisited(Value *p);

    /**
     * setFatherDir.
     * @param dir the direction of the 'father' of the Square of the given Value relative to the
     *            Square.
     * @param p the Value (coordinate) of the Square that will be linked to its 'father'.
     * This function links between a Square and its 'father'.
     */
    void setFatherDir(int dir, Value *p);

    /**
     * Destructor.
     */
    ~Matrix();

    /**
     * getValue.
     * @param x the x coordinate of a Value in this Matrix.
     * @param y the y coordinate of a Value in this Matrix.
     * @return the Value which its coordinate is the given x and the given y.
     */
    Value *getValue(int x, int y);

    /**
     * resetVisitedSquares - mark all Squares in GriMatrix as not-visited.
     */
    void resetVisitedSquares();
};


#endif //ASS1_MATRIX_H