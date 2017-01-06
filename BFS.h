#ifndef EX2_BFS_H
#define EX2_BFS_H

#include <iostream>
#include <queue>
#include <stack>
#include "Point.h"
#include "Square.h"
#include "Matrix.h"
#include "Element.h"
#include <list>
#include "Map.h"

/**
 * BFS class- this class implments the BFS algorithm. This class finds the shortest path between
 * 2 coordinates in a Grid (graph) and prints it.
 */
class BFS {
private:
    Grid *grid;
    std::queue<Element *> *option;
    std::list<Element *> *path;
    /*TODO*/
    Map *map;

    void createPath(Value *source, Element *current);

public:
    std::list<Element *> *pathDrive(Value *source, Value *destination);

    /**
     * printPath.
     * @param source the start coordinate (Value) of the path.
     * @param current the current coordinate (Value) in the path.
     * This function prints the coordinates of the Elements in the path.
     */
    void printPath(Value *source, Element *current);

    /**
     * Constructor.
     * @param source the coordinate (Value) of the start of the path.
     * @param destination the coordinate (Value) of the end of the path.
     * @param g the Grid (graph) which the BFS algorithm search on.
     */
    BFS(Map *map);

    /**
     * Destructor.
     */
    ~BFS();
};

#endif //TRY_BFS_H