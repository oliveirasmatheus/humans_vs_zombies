#ifndef _Zombie_H
#define _Zombie_H

#include <vector>

#include "Organism.h"
#include "City.h"

class Zombie: public Organism {

private:
    int timeTillStarve;
    //given a coordinate of the cell (x,y),
    //returns a list of valid moves to adjacent ants

    std::vector<int> getMovesToHumans(int x, int y) const;

public:
    Zombie(): Organism(), timeTillStarve(0){}
    Zombie(City* city, int x, int y);
    void breed();
    void move();
    void turn() override;
    int getType() override { return ZOMBIE_CH; }
    bool starves() override { return timeTillStarve == 0; }
};

#endif