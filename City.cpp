// City.cpp
#include <cstdlib>
#include <random>

#include "City.h"
#include "Organism.h"
#include "GameSpecs.h"
#include "Human.h"
#include "Zombie.h"

using namespace std;

int City::generateRandomNumber(int startRange, int endRange) const {
    return rand() % (endRange - startRange + 1) + startRange;
}

City::City(){
    srand(time(NULL));
    timeStepCount = 0;
    for (int x = 0; x < GRID_SIZE; x++)
        for (int y = 0; y < GRID_SIZE; y++)
            grid[x][y] = nullptr;

    // Create and place initial humans
    for (int i = 0; i < HUMAN_START_COUNT; ++i) {
        int x = rand() % (GRID_SIZE / 2);  // Random x coordinate within half of the grid width
        int y = rand() % (GRID_SIZE / 2); // Random y coordinate within half of the grid height

        // Distribute humans in each quadrant
        x += (i % 2) * (GRID_SIZE / 2);    // Shift x coordinate for alternating columns
        y += (i / (HUMAN_START_COUNT / 2)) * (GRID_SIZE / 2);   // Shift y coordinate for each quadrant

        // Check if the chosen cell is empty before placing a human
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Human(this, x, y);
        } else {
            --i;
        }
    }

    // Create and place initial zombies
    for (int i = 0; i < ZOMBIE_START_COUNT; ++i) {
        int x = rand() % (GRID_SIZE / 2);  // Random x coordinate within half of the grid width
        int y = rand() % (GRID_SIZE / 2); // Random y coordinate within half of the grid height

        // Distribute zombies in each quadrant
        x += (i % 2) * (GRID_SIZE / 2);    // Shift x coordinate for alternating quadrants
        y += (i / (ZOMBIE_START_COUNT / 2)) * (GRID_SIZE / 2); // Shift y coordinate for each quadrant

        // Check if the chosen cell is empty before placing a zombie
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Zombie(this, x, y);
        } else {
            --i;
        }
    }
}

void City::takeTimeStep(){
    timeStepCount++;

    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (grid[x][y] != nullptr) {
                grid[x][y]->turn();
            }
        }
    }

    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (grid[x][y] != nullptr && grid[x][y]->starves()) {
                delete grid[x][y];
                grid[x][y] = new Human(this, x, y); // if starves add a human in this place
            }
        }
    }

    // Reset moved flag for the next time step
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            if (grid[x][y] != nullptr) {
                grid[x][y]->setMoved(false);
            }
        }
    }
}
int City::getGeneration() {
    return timeStepCount;
}

int City::countType(char organismType) {
    int count = 0;

    // Iterate through the grid to count organisms of a specific type
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            if (grid[i][j] != nullptr && grid[i][j]->getType() == organismType) {
                count++;
            }
        }
    }

    return count;
}

std::ostream& operator<<(std::ostream& output, const City& city) {
    for (int x = 0; x < GRID_SIZE; x++){
        for (int y = 0; y < GRID_SIZE; y++){
            if (city.grid[x][y] != nullptr) {
                if (city.grid[x][y]->getType() == ZOMBIE_CH) {
                    output << "\033[38;5;" << ZOMBIE_COLOR << "m";
                    output << 'Z' << "  ";
                } else if (city.grid[x][y]->getType() == HUMAN_CH) {
                    output << "\033[38;5;" << HUMAN_COLOR << "m";
                    output << 'H' << "  ";
                }
                output << "\033[0m"; // Reset text color to default
            } else {
                output << SPACE_CH << "  ";
            }
        }
        output << std::endl;
    }

    return output;
}