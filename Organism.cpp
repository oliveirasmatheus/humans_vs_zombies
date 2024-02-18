#include "Organism.h"
#include "Human.h"
#include "GameSpecs.h"

std::vector<int> Organism::getMovesToEmptyCells(int x, int y) const {
    std::vector<int> movesToEmptyCells;
    int tempX, tempY;
    for (int move = LEFT; move <= UP; move++){
        tempX = x;
        tempY = y;
        getCoordinate(tempX, tempY, move);
        if (!isValidCoordinate(tempX, tempY)) continue;
        if (city->grid[tempX][tempY] == nullptr)
            movesToEmptyCells.push_back(move);
    }
    return movesToEmptyCells;
}

bool Organism::isValidCoordinate(int x, int y) const {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE)
        return false;
    return true;
}

void Organism::getCoordinate(int& x, int& y, int move) const {
    switch (move) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case DOWN: y--; break;
        case UP: y++; break;
        case UP_LEFT: y++; x--; break;
        case UP_RIGHT: y++; x++; break;
        case DOWN_LEFT: y--; x--; break;
        case DOWN_RIGHT: y--; x++; break;
    }
}

Organism::Organism(City* city, int x, int y){
    this->city = city;
    this->x = x;
    this->y = y;
    timeTillBreed = 0;
    timeStepCount = city->timeStepCount;
}

void Organism::turn() {}