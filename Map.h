#ifndef EX2_MAP_H
#define EX2_MAP_H

#include "Grid.h"
#include "Value.h"
#include <list>

/**
 * Map class - a class of a single Map. This map contains a Grid and a list of obstacles in the map
 * (in the world).
 */
class Map {
private:
    std::list<Value *> obstacles;
    Grid *grid;
public:
    /**
     * Constructor.
     * @param obstacle a list which holds the obstacles in the map (in the world).
     * @param sizes the sizes of the map (of the world).
     */
    Map(std::list<Value *> obstacle, std::list<int> *sizes);

    /**
     * Defualt constructor.
     */
    Map();

    /**
     * getGrid.
     * @return the grid of this Map.
     */
    Grid *getGrid();

    /**
     * isValueAnObstacle.
     * @param value a Value which the user wants to know whether it is an obstacle or not.
     * @return 'true' if this Value is an obstacle. Otherwise, returns 'false'.
     */
    bool isValueAnObstacle(Value *value);

    /**
     * Destructor.
     */
    ~Map();

    /**
     * GetObstacles.
     * @return a list which contains the obstacles in this Map.
     */
    std::list<Value *> GetObstacles();
};

#endif