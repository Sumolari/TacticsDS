#ifndef CONSTANTS_H
#define CONSTANTS_H

#define MAX_TEAMS 2

#define MIN(a,b) ( a > b ) ? a : b

#define COST_CELL_INFINITY  9999
#define COST_CELL_BASE      1
#define COST_CELL_BRIDGE    1
#define COST_CELL_FOREST    2
#define COST_CELL_GRASS     1
#define COST_CELL_MOUNTAIN  3
#define COST_CELL_RIVER     COST_CELL_INFINITY

#endif