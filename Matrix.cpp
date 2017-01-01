#include "Matrix.h"

Matrix::Matrix(int x, int y) {
    this->xSize = x;
    this->ySize = y;
    this->matrix = new Square **[this->xSize];
    for (int i = 0; i < this->xSize; i++) {
        this->matrix[i] = new Square *[this->ySize];
    }

    for (int i = 0; i < this->xSize; i++) {
        for (int j = 0; j < this->ySize; j++) {
            this->matrix[i][j] = new Square(new Point(i, j));
            if (i - 1 >= 0) {

                this->matrix[i][j]->setLeftNeighbor(new Point(i - 1, j));
            }
            if (j + 1 < this->ySize) {
                this->matrix[i][j]->setUpNeighbor(new Point(i, j + 1));
            }
            if (i + 1 < this->xSize) {
                this->matrix[i][j]->setRightNeighbor(new Point(i + 1, j));
            }
            if (j - 1 >= 0) {
                this->matrix[i][j]->setDownNeighbor(new Point(i, j - 1));
            }
        }
    }
}

bool Matrix::compareVectors(Value *p1, Value *p2) {
    if ((p1->getiValue(1) == p2->getiValue(1)) && (p1->getiValue(2) == p2->getiValue(2))) {
        return true;
    } else {
        return false;
    }
}

Value *Matrix::getMyCoordinate(Element *s) {
    return s->getMyLocation();
}

Element *Matrix::getSquare(Value *p) {
    if ((p->getiValue(1) >= 0) && (p->getiValue(1) < this->xSize) &&
        (p->getiValue(2) >= 0) && (p->getiValue(2) < this->ySize)) {
        return this->matrix[p->getiValue(1)][p->getiValue(2)];
    } else {
        return NULL;
    }
}

void Matrix::setVisitSquare(Value *p) {
    this->matrix[p->getiValue(1)][p->getiValue(2)]->setVisit();
}

bool Matrix::isVisited(Value *p) {
    return this->matrix[p->getiValue(1)][p->getiValue(2)]->ifVisited();
}

void Matrix::setFatherDir(int dir, Value *p) {
    this->matrix[p->getiValue(1)][p->getiValue(2)]->setFatherDirection(dir);
}

Matrix::~Matrix() {
    for (int i = 0; i < this->xSize; i++) {
        for (int j = 0; j < this->ySize; j++) {
            delete (this->matrix[i][j]);
        }
        delete[](this->matrix[i]);
    }
    delete this->matrix;
}

Value *Matrix::getValue(int x, int y) {
    if (x >= 0 && x < this->xSize && y >= 0 && y <= ySize) {
        Value *p = this->matrix[x][y]->getMyLocation();
        return p;
    } else
        return NULL;
}

void Matrix::resetVisitedSquares() {
    for (int i = 0; i < this->xSize; i++) {
        for (int j = 0; j < this->ySize; j++) {
            this->matrix[i][j]->setUnvisited();
        }
    }
}