#ifndef EX2_GRID_H
#define EX2_GRID_H

#include "Point.h"
#include "Square.h"

/**
 * Grid class- this calss represents a graph.
 */
class Grid {
private:
    int numberOfElements;
    int *sizesOfAxises;
public:
    /**
     * compareVectors.
     * @param p1 a vector which will be compared to 'p2'.
     * @param p2 a vector which will be compared to 'p1'.
     * @return 'true' if p1 equals to p2. Else, returns 'false'.
     * Note: This comparison is based on the values of the parameters in the vectors (not whether
     *       these vectors have the same address).
     */
    virtual bool compareVectors(Value *p1, Value *p2)=0;

    /**
     * getMyCoordinate.
     * @param s an Element in this Grid.
     * @return the Value (coordinate) of this Element on this Grid.
     */
    virtual Value *getMyCoordinate(Element *s)=0;

    /**
     * setVisitSquare.
     * @param p a Value in this Grid that has been visited.
     * This function marks the Element of the given Value as visited.
     */
    virtual void setVisitSquare(Value *p)=0;

    /**
     * isVisited.
     * @param p a Value of an Element in this Grid.
     * @return 'true' if the Element of the given Value has been visited. Else, returns 'false'.
     */
    virtual bool isVisited(Value *p)=0;

    /**
     * setFatherDir.
     * @param dir the direction of the 'father' of the Element of the given Value relative to the
     *            Element.
     * @param p the Value of the Element that will be linked to its 'father'.
     * This function links between an Element and its 'father'.
     */
    virtual void setFatherDir(int dir, Value *p)=0;

    /**
     * getSquare.
     * @param p a Value of an Element in this Grid.
     * @return the Element that the given Value is its coordinate in this Grid.
     */
    virtual Element *getSquare(Value *p)=0;

    /*
     * resetVisitedSquares - mark all Elements in Grid as not-visited.
     */
    virtual void resetVisitedSquares()=0;

    /**
     * Destructor.
     */
    virtual ~Grid() {
    };
};

#endif //ASS1_GRID_H