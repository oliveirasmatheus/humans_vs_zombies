#include "Zombie.h"
#include "City.h"
#include "GameSpecs.h"
#include "Human.h"
#include <vector>

using namespace std;

vector<int> Zombie::getMovesToHumans(int x, int y) const {
    vector<int> movesToHumans;
    int tempX, tempY;
    for (Direction move = LEFT; move <= DOWN_RIGHT; move = static_cast<Direction>(static_cast<int>(move) + 1)) {
        tempX = x;
        tempY = y;
        getCoordinate(tempX, tempY, move);
        if (!isValidCoordinate(tempX, tempY)) continue;
        if (city->grid[tempX][tempY] == nullptr) continue;
        if (city->grid[tempX][tempY]->getType() == HUMAN_CH)
            movesToHumans.push_back(move);
    }

    return movesToHumans;
}

Zombie::Zombie(City* city, int x, int y): Organism(city, x, y){
    timeTillStarve = ZOMBIE_STARVE;
    timeTillBreed = ZOMBIE_BREED;
}

void Zombie::breed(){
    timeTillBreed--;
    if (timeTillBreed > 0) return;
    vector<int> humanToBreed = getMovesToHumans(x, y);
    if (humanToBreed.size() == 0) return; // no humans around
    int randomMove = humanToBreed[city->generateRandomNumber(0, humanToBreed.size() - 1)];
    int newX = x;
    int newY = y;
    getCoordinate(newX, newY, randomMove);
    city->grid[newX][newY] = new Zombie(city, newX, newY);
    timeTillBreed = ZOMBIE_BREED;
}

void Zombie::move(){
    if (hasMoved()) return;
    if (timeStepCount == city->timeStepCount) return;
    vector<int> movesToHumans = getMovesToHumans(x, y);
    if (movesToHumans.size() == 0){ // No humans, move to random position
        timeTillStarve--;

        int randomMove = city->generateRandomNumber(LEFT, DOWN_RIGHT);
        int newX = x;
        int newY = y;
        getCoordinate(newX, newY, randomMove);

        if (isValidCoordinate(newX, newY) && city->grid[newX][newY] == nullptr) {
            // If the new position is valid and empty, move the organism
            city->grid[x][y] = nullptr;
            city->grid[newX][newY] = this;
            x = newX;
            y = newY;
        }

    } else {
        timeStepCount++;
        timeTillStarve = ZOMBIE_STARVE; // has human to eat, reset starve
        int randomMove = movesToHumans[city->generateRandomNumber(0, movesToHumans.size() - 1)];
        int humanX = x;
        int humanY = y;
        getCoordinate(humanX, humanY, randomMove);
        delete city->grid[humanX][humanY];
        city->grid[humanX][humanY] = this;
        city->grid[x][y] = nullptr;
        x = humanX;
        y = humanY;
    }
}

void Zombie::turn() {
    move();
    breed();
    setMoved(true);
}

