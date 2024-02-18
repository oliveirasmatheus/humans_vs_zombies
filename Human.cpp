#include "GameSpecs.h"
#include "City.h"
#include "Organism.h"
#include "Human.h"

#include <vector>

using namespace std;

Human::Human(City* city, int x, int y): Organism(city, x, y){
    timeTillBreed = HUMAN_BREED;
}

void Human::recruit() {
    // Check if it's not time to breed yet
    if (timeTillBreed > 0) return;

    // Get valid moves to empty cells around the current position
    vector<int> validMoves = getMovesToEmptyCells(x, y);

    // If there are no valid moves (no empty cells around), set timeTillBreed and return
    if (validMoves.size() == 0) {
        timeTillBreed = HUMAN_BREED;
        return;
    }

    // Choose a random move from the valid moves
    int randomMove = validMoves[city->generateRandomNumber(0, validMoves.size() - 1)];

    // Calculate the new position based on the random move
    int newX = x;
    int newY = y;
    getCoordinate(newX, newY, randomMove);

    // Create a new Human at the new position in the city's grid
    city->grid[newX][newY] = new Human(city, newX, newY);

    // Set timeTillBreed to the breeding time
    timeTillBreed = HUMAN_BREED;
}

void Human::move() {
    if (hasMoved()) return;
    if (timeStepCount == city->timeStepCount) return;
    timeStepCount++;
    timeTillBreed--;

    // Initialize a vector to store valid moves
    vector<int> validMoves;

    // Generate a random move in the allowed range (up, down, left, or right)
    for (int move = LEFT; move <= DOWN; move = move + 2) {
        int newX = x;
        int newY = y;
        getCoordinate(newX, newY, move);

        // Check if the new position is valid and empty
        if (isValidCoordinate(newX, newY) && city->grid[newX][newY] == nullptr) {
            validMoves.push_back(move);
        }
    }

    // If there are no valid moves, return without moving
    if (validMoves.empty()) {
        return;
    }

    // Randomly choose a move from the vector of valid moves
    int randomMove = validMoves[city->generateRandomNumber(0, validMoves.size() - 1)];

    int newX = x;
    int newY = y;
    getCoordinate(newX, newY, randomMove);

    // Move the organism to the randomly chosen position
    city->grid[x][y] = nullptr;
    city->grid[newX][newY] = this;
    x = newX;
    y = newY;
}



void Human::turn() {
    move();
    recruit();
    setMoved(true);
}