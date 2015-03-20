#ifndef TURN_MANAGER_H
#define TURN_MANAGER_H

#include "./player.h"

namespace TurnManager {

/**
 * Adds given player to the game.
 * @param player Adds player to the game.
 */
void addPlayer(Player *player);

/**
 * Returns the amount of players in the match.
 * @return Amount of players in the match.
 */
int numPlayers();

/**
 * Returns the ID of the currently player.
 * @return ID of the currently playing player.
 */
PlayerID currentPlayerID();

/**
 * Resets manager, removing all players.
 */
void reset();

/**
 * Ends turn of current player and starts turn of next one.
 * @return Ends turn of current player and starts turn of next one.
 */
void finishTurn();

/**
 * Returns whether game should finish or not.
 * @return True if game should finish.
 */
bool gameShouldFinish();

}; // namespace TurnManager

#endif