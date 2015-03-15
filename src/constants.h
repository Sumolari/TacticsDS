#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * Maximum amount of teams in a match.
 */
#define MAX_TEAMS 2

/**
 * Computes the minimum between two numbers.
 */
#define MIN(a,b) ( a > b ) ? a : b

/**
 * Infinity cost.
 */
#define COST_CELL_INFINITY  9999
/**
 * Cost of entering a base cell.
 */
#define COST_CELL_BASE      1
/**
 * Cost of entering a bridge cell.
 */
#define COST_CELL_BRIDGE    1
/**
 * Cost of entering a forest cell.
 */
#define COST_CELL_FOREST    2
/**
 * Cost of entering a grass cell.
 */
#define COST_CELL_GRASS     1
/**
 * Cost of entering a mountain cell.
 */
#define COST_CELL_MOUNTAIN  3
/**
 * Cost of entering a river cell.
 */
#define COST_CELL_RIVER     COST_CELL_INFINITY

/**
 * ID of none owner.
 */
#define UNIT_OWNER_NONE     -1

/**
 * ID of no unit type.
 */
#define UNIT_TYPE_EMPTY     0
/**
 * ID of Warrior unit type.
 */
#define UNIT_TYPE_WARRIOR   1

#endif