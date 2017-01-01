#include <iostream>
#include "BFS.h"

BFS::BFS(Map *map){
    this->map=map;
    this->grid=map->getGrid();
}

std::list<Element*>* BFS:: pathDrive(Value* source,Value* destination) {
    this->grid->resetVisitedSquares();
    Element *current;
    if(source->getiValue(1)==destination->getiValue(1)
       && source->getiValue(2)==destination->getiValue(2)){
        current = this->grid->getSquare(destination);
    } else {
        //create a queue which will contain the optional paths.
        this->option = new std::queue<Element *>;
        option->push(grid->getSquare(source));
        this->grid->setVisitSquare(source);
        /**
         * this loop goes over the 'Element's in 'Grid' g and create the optional paths which are
         * inserted to Queue "option". This loop ends when one of the paths get to the destination
         * point.
         */
        /*TODO*/
        while (!option->empty()) {
            current = this->option->front();
            this->option->pop();
            //If one of the paths get to 'destination'.
            if (grid->compareVectors(destination, grid->getMyCoordinate((current)))) {
                current->setVisit();
                break;
            } else {
                //If current has a left neighbor that hasn't been visited.
                if ((current->hasLeftNeighbor()) &&
                    (!this->grid->isVisited(current->getLeftNeighbor()))&&
                    !this->map->isValueAnObstacle(current->getLeftNeighbor()) ) {
                    this->option->push(this->grid->getSquare(current->getLeftNeighbor()));
                    this->grid->setVisitSquare(current->getLeftNeighbor());
                    this->grid->setFatherDir(1, current->getLeftNeighbor());
                }
                //If current has a upper neighbor that hasn't been visited.
                if ((current->hasUpNeighbor()) &&
                    (!this->grid->isVisited(current->getUpNeighbor()))&&
                    !this->map->isValueAnObstacle(current->getUpNeighbor())) {
                    this->option->push(this->grid->getSquare(current->getUpNeighbor()));
                    this->grid->setVisitSquare(current->getUpNeighbor());
                    this->grid->setFatherDir(2, current->getUpNeighbor());
                }
                //If current has a right neighbor that hasn't bee visited.
                if (current->hasRightNeighbor() &&
                    !this->map->isValueAnObstacle(current->getRightNeighbor())&&
                    (!this->grid->isVisited(current->getRightNeighbor()))) {
                    this->option->push(grid->getSquare(current->getRightNeighbor()));
                    this->grid->setVisitSquare(current->getRightNeighbor());
                    this->grid->setFatherDir(3, current->getRightNeighbor());
                }
                //If current has a down neighbor that hasn't been visited.
                if (current->hasDownNeighbor() &&
                    !this->map->isValueAnObstacle(current->getDownNeighbor())&&
                    (!this->grid->isVisited(current->getDownNeighbor()))) {
                    this->option->push(grid->getSquare(current->getDownNeighbor()));
                    this->grid->setVisitSquare(current->getDownNeighbor());
                    this->grid->setFatherDir(4, current->getDownNeighbor());
                }
            }
        }
    }
    this->path=new std::list<Element *>;
    createPath(source,current);
    if(this->option!=NULL) {
        delete (this->option);
        this->option = NULL;
    }
    return this->path;
}

void BFS::printPath(Value* source, Element* current) {
    //If source equals to current.
    if(this->grid->compareVectors(source, current->getMyLocation())){
        current->getMyLocation()->printValue();
        return;
    } else {
        printPath(source, this->grid->getSquare(current->getFatherCoordinate()));
        current->getMyLocation()->printValue();
    }
}

BFS::~BFS() {
    if(this->option!=NULL) {
        delete (this->option);
    }
}


void BFS::createPath(Value *source, Element *current) {
    //If source equals to current.
    if(this->grid->compareVectors(source, current->getMyLocation())){
        this->path->push_front(this->grid->getSquare(current->getMyLocation()));
    } else {
        // printPath(source, this->grid->getSquare(current->getFatherCoordinate()));
        this->path->push_front(this->grid->getSquare(current->getMyLocation()));
        createPath(source,this->grid->getSquare(current->getFatherCoordinate()));
    }
}

