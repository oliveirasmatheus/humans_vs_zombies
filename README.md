# Human vs. Zombie: A C++ Console Application

Welcome to Human vs. Zombie, a simple predator-prey simulation game implemented in C++.

In this game, the prey are represented by humans "H" and the predators are zombies "Z". They inhabit a 20x20 grid of cells where only one creature may occupy a cell at a time, and no creature may move off the edges of the world.

## Game Rules:
- Time is simulated in discrete time steps, with each critter performing actions in each step.
- Actions for humans:
  - Move: Humans randomly move up, down, right, or left. If the selected direction is occupied or would move off the grid, the human remains in the current cell.
  - Breed: If a human survives for three time steps, it breeds, creating a new human in an adjacent empty cell.
- Actions for zombies:
  - Move: Zombies randomly move up, down, right, or left. If an adjacent cell contains a human, the zombie eats it and moves into that cell. Otherwise, it moves like a human.
  - Breed: Zombies breed after surviving for eight time steps, creating a new zombie in an adjacent empty cell.
  - Starve: Zombies die if they haven't eaten a human within the last three time steps.

## Gameplay:
- Doodlebugs move first, followed by humans. Both breed simultaneously.
- At the end of each time step, some doodlebugs may starve.

## Representation:
- "H": Represents a human.
- "Z": Represents a zombie.
- "-": Represents an empty cell.

## Initialization:
- The world starts with 5 zombies and 100 humans.

Enjoy playing Human vs. Zombie! May the strongest survive.
