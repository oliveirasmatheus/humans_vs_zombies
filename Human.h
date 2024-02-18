#ifndef _Human_H
#define _Human_H

#include "Organism.h"
#include "City.h"

class Human: public Organism {

public:
    Human(): Organism(){}
    Human(City* city, int x, int y);
    void recruit();
    void move();
    int getType() override { return HUMAN_CH; }
    void turn() override;

};

#endif