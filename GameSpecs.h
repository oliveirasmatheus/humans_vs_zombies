#ifndef _GAMESPECS_H
#define _GAMESPECS_H


const int GRID_SIZE = 20;
const int ZOMBIE_START_COUNT = 5;
const int HUMAN_START_COUNT = 100;
const int ZOMBIE_BREED = 8;
const int HUMAN_BREED = 3;
const int ZOMBIE_STARVE = 3;
const char HUMAN_CH = 72;//72 "H"// ascii for Human   was 111 why?
const char SPACE_CH = 45; // "-" ascii dash for empty elements
const char ZOMBIE_CH = 90;//90 "Z"// ascii for zombie
const double PAUSE_SECONDS = 0.9; // pause between steps
const int ITERATIONS = 1000; // max number of steps
const int HUMAN_COLOR = 14; // turquoise
const int ZOMBIE_COLOR = 3; // bright yellow

#endif