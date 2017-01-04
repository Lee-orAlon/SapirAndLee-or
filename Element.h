#ifndef EX2_ELEMENT_H
#define EX2_ELEMENT_H


#include "Value.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include "Value.h"
/**
 * Element class- this class represents a location of an Element in a Grid.
 */
class Element {
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    }
public:
    /**
     * setLeftNeighbor.
     * @param left the left neighbor of this Element in the Grid.
     * This function links between an Element and its left neighbor.
     */
    virtual void setLeftNeighbor(Value *left)=0;

    /**
     * setRightNeighbor.
     * @param right the right neighbor of this Element in the Grid.
     * This function links between an Element and its right neighbor.
     */
    virtual void setRightNeighbor(Value *right)=0;

    /**
     * setUpNeighbor.
     * @param up the neighbor above this Element in the Grid.
     * This function links between an Element and its neighbor above.
     */
    virtual void setUpNeighbor(Value *up)=0;

    /**
     * setDownNeighbor.
     * @param down the neighbor below this Element in the Grid.
     * This function links between an Element and its neighbor below.
     */
    virtual void setDownNeighbor(Value *down)=0;

    /**
     * getMyLocation.
     * @return the location (coordinate) of this Element in the Grid.
     */
    virtual Value *getMyLocation()=0;

    /**
     * setVisit.
     * Mark that this Element as "been visited", means this Element has been passed.
     */
    virtual void setVisit()=0;

    /**
     * hasLeftNeighbor.
     * @return 'true' if this Element has a left neigbor in the Grid. Else, returns 'false'.
     */
    virtual bool hasLeftNeighbor()=0;

    /**
     * hasRightNeighbor.
     * @return 'true' if this Element has a right neigbor in the Grid. Else, returns 'false'.
     */
    virtual bool hasRightNeighbor()=0;

    /**
     * hasUpNeighbor.
     * @return 'true' if this Element has a neigbor above in the Grid. Else, returns 'false'.
     */
    virtual bool hasUpNeighbor()=0;

    /**
     * hasDownNeighbor.
     * @return 'true' if this Element has a neigbor below in the Grid. Else, returns 'false'.
     */
    virtual bool hasDownNeighbor()=0;

    /**
     * getLeftNeighbor.
     * @return the left neighbor of this Element in the Grid.
     * Note: If this Element doesn't have a left neighbor, then the returned value will be 'NULL'.
     */
    virtual Value *getLeftNeighbor()=0;

    /**
     * getRightNeighbor.
     * @return the right neighbor of this Element in the Grid.
     * Note: If this Element doesn't have a right neighbor, then the returned value will be 'NULL'.
     */
    virtual Value *getRightNeighbor()=0;

    /**
     * getUpNeighbor.
     * @return the neighbor above this Element in the Grid.
     * Note: If this Element doesn't have a neighbor above, then the returned value will be 'NULL'.
     */
    virtual Value *getUpNeighbor()=0;

    /**
     * getDownNeighbor.
     * @return the neighbor below this Element in the Grid.
     * Note: If this Element doesn't have a neighbor below, then the returned value will be 'NULL'.
     */
    virtual Value *getDownNeighbor()=0;

    /**
     * ifVisited.
     * @return 'true' if this Element has been visited (if this Element has been passed).
     *          Else, returns 'false'.
     */
    virtual bool ifVisited()=0;

    /**
     * setFatherDirection.
     * @param direction the direction of this Element's 'father' (the Element that is before this
     *                  Element in the path) relative to this Element.
     * This function links between an Element and its 'father'.
     */
    virtual void setFatherDirection(int direction)=0;

    /**
     * getFatherCoordinate.
     * @return this Element's father coordinate (Value) in the Grid.
     */
    virtual Value *getFatherCoordinate()=0;

    virtual bool hasFatherDirection()=0;
};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(Element)
#endif //ASS1_ELEMENT_H