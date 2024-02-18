#ifndef _Organism_H
#define _Organism_H

#include <iostream>
#include <vector>

#include "City.h"

class City;

class Organism {

protected:
    City *city;
    int x;
    int y;
    int timeTillBreed;
    int timeStepCount;
    bool moved;
    enum Direction {
        LEFT = 1,
        RIGHT,
        DOWN,
        UP,
        UP_LEFT,
        UP_RIGHT,
        DOWN_LEFT,
        DOWN_RIGHT
    };
    std::vector<int> getMovesToEmptyCells(int x, int y) const;
    bool isValidCoordinate(int x, int y) const;
    void getCoordinate(int& x, int& y, int move) const;

public:
    Organism(): city(nullptr), x(0), y(0), timeTillBreed(0), timeStepCount(0){}
    Organism(City *city, int x, int y);

    bool hasMoved() const { return moved; }
    void setMoved(bool value) { moved = value; }

    virtual void turn();
    virtual int getType() = 0;
    virtual bool starves() { return false; }

};

#endif
