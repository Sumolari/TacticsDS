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
    /**
     * Creates a new AI player.
     */
    explicit PlayerAI(Grid *grid, std::function<void(void)> callback);

    /**
     * Creates a new AI player given its ID.
     */
    explicit PlayerAI(Grid *grid, std::function<void(void)> callback,
                      PlayerID ID);

    virtual void startTurn();

    virtual void print();

    virtual ~PlayerAI() = default;
};

#endif