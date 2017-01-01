#include "Map.h"
#include "Matrix.h"

Map::Map(std::list<Value *> obstacle, std::list<int> *sizes) {
    this->obstacles = obstacle;
    if (sizes > 0) {
        std::list<int>::iterator it = sizes->begin();
        this->grid = new Matrix((*it), (*(++it)));
    }
}

Map::Map() {
}

Map::~Map() {
    Value *val;
    for (std::list<Value *>::iterator it = this->obstacles.begin();
         it != this->obstacles.end(); it++) {
        val = (*it);
        (*it) = NULL;
        delete (val);
    }
}

Grid *Map::getGrid() {
    return this->grid;
}

bool Map::isValueAnObstacle(Value *value) {
    if (!this->obstacles.empty()) {
        for (std::list<Value *>::iterator it = this->obstacles.begin();
             it != this->obstacles.end(); it++) {
            if (value->getiValue(1) == (*it)->getiValue(1) &&
                value->getiValue(2) == (*it)->getiValue(2))
                return true;
        }
    }
    return false;
}

std::list<Value *> Map::GetObstacles() {
    return this->obstacles;
}