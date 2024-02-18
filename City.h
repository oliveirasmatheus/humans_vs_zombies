#ifndef _CITY_H
#define _CITY_H

#include <iostream>
#include "GameSpecs.h"
#include "Organism.h"

class Organism;

class City {

    friend class Organism;
    friend class Human;
    friend class Zombie;

private:
    Organism *grid[GRID_SIZE][GRID_SIZE];
    int timeStepCount;
    int generateRandomNumber(int startRange, int endRange) const;

public:
    City();
    void takeTimeStep();
    int getGeneration();
    int countType(char organismType);

    friend std::ostream& operator<<(std::ostream& output, const City& city);
};

#endif
