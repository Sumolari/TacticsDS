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

/**
 * Returns winner player's ID.
 * @return Winner player's ID.
 */
PlayerID getWinner();

/**
 * Sets winner player.
 * @param winnerID New winner's player ID.
 */
void setWinner(PlayerID winnerID);

/**
 * Resets winner player so there is not winner player.
 */
void resetWinner();

/**
 * Returns wether player currently playing is an AI or not.
 * @return True if playing currently playing is an AI, false otherwise.
 */
bool AIPlaying();

}; // namespace TurnManager

#endif