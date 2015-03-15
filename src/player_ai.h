#ifndef PLAYER_AI_H
#define PLAYER_AI_H

#include "./player_ai.h"

#include <functional>

#include "./grid.h"


class PlayerAI : public Player {
  private:
    /**
     * Pointer to the grid.
     */
    Grid *grid;

    /**
     * Callback to be called when turn has finished.
     */
    std::function<void(void)> onFinishTurnCallback;

    /**
     * Random seed.
     */
    unsigned int seed;

    /**
     * Iterator used to check units.
     */
    unsigned long int unitNumber;

  public:
    PlayerAI(Grid *grid, std::function<void(void)> callback) :
        grid(grid),
        onFinishTurnCallback(callback),
        seed(42) {};

    /**
     * Tells this player that he can start playing.
     */
    virtual void startTurn();

};

#endif