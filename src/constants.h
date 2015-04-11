#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * Import sound constants.
 */
#include "./soundbank.h"

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
#define COST_MOVE_CELL_BASE      1
/**
 * Cost of entering a bridge cell.
 */
#define COST_MOVE_CELL_BRIDGE    1
/**
 * Cost of entering a forest cell.
 */
#define COST_MOVE_CELL_FOREST    2
/**
 * Cost of entering a grass cell.
 */
#define COST_MOVE_CELL_GRASS     1
/**
 * Cost of entering a mountain cell.
 */
#define COST_MOVE_CELL_MOUNTAIN  3
/**
* Cost of entering a castle cell.
*/
#define COST_MOVE_CELL_CASTLE    1
/**
 * Cost of entering a river cell.
 */
#define COST_MOVE_CELL_RIVER     COST_CELL_INFINITY

/**
 * Cost of seeing through a base cell.
 */
#define COST_SEE_CELL_BASE      1
/**
 * Cost of seeing through a bridge cell.
 */
#define COST_SEE_CELL_BRIDGE    1
/**
 * Cost of seeing through a forest cell.
 */
#define COST_SEE_CELL_FOREST    5
/**
 * Cost of seeing through a grass cell.
 */
#define COST_SEE_CELL_GRASS     1
/**
 * Cost of seeing through a mountain cell.
 */
#define COST_SEE_CELL_MOUNTAIN  4
/**
 * Cost of seeing through a castle cell.
 */
#define COST_SEE_CELL_CASTLE    1
/**
 * Cost of entering a river cell.
 */
#define COST_SEE_CELL_RIVER     1
/**
 * Default defense value.
 */
#define DEFAULT_DEFENSE        0
/**
 * Defense given by a base cell.
 */
#define DEFENSE_CELL_BASE      DEFAULT_DEFENSE
/**
 * Defense given by a bridge cell.
 */
#define DEFENSE_CELL_BRIDGE    DEFAULT_DEFENSE
/**
 * Defense given by a forest cell.
 */
#define DEFENSE_CELL_FOREST    1
/**
 * Defense given by a grass cell.
 */
#define DEFENSE_CELL_GRASS     DEFAULT_DEFENSE
/**
 * Defense given by a mountain cell.
 */
#define DEFENSE_CELL_MOUNTAIN  2
/**
 * Defense given by a river cell.
 */
#define DEFENSE_CELL_RIVER     DEFAULT_DEFENSE

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
/**
 * ID of Knight unit type.
 */
#define UNIT_TYPE_KNIGHT   2
/**
 * ID of Sniper unit type.
 */
#define UNIT_TYPE_SNIPER   3


/**
 * Name of the file that will be used to store saved games.
 */
#define DEFAULT_SAVEGAME_FILE "savegame.txt"

#endif
