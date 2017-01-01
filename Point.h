#ifndef EX2_POINT_H
#define EX2_POINT_H

#include "Value.h"

/**
 * Point class- represents a point (x,y) in 2D world. This class extends the 'Value' class.
 */
class Point : public Value {
private:
    int x;
    int y;
public:
    /**
     * Constructor.
     * @param xValue - the value of the point in x axis.
     * @param yValue - the value of the point in y axis.
     */
    Point(int xValue, int yValue);

    /**
     * getX.
     * @return the value of the point in x axis.
     */
    int getX();

    /**
     * geyY.
     * @return the value of the point in y axis.
     */
    int getY();

    /**
     * getiValue.
     * @param i the i-th parameter in the vector which represents the point (in Point class the
     * lengd of the vector is 2)
     * @return the value of the i-th parameter of the vector.
     */
    int getiValue(int i);

    /**
     * printValue.
     * Prints the vector in the following format: (x,y)
     */
    void printValue();

    /**
     * Destructor.
     */
    ~Point();

    bool operator==(const Point &other) const;

    bool operator!=(const Point &other) const;
};

#endif //TRY_POINT_H