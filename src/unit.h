#ifndef UNIT_H
#define UNIT_H

#include "./FMAW.h"

#include "./player.h"

class Unit : public FMAW::Character {
  protected:
    /**
     * ID of player who owns this unit.
     */
    PlayerID ownerID;


    virtual void init();
  public:
    /**
     * Amount of movement points that this Unit has available.
     */
    int movementCapacity;

    /**
     * Maximum amount of available actions this Unit has.
     */
    int maximumAvailableActions;

    /**
     * Amount of remaining available actions this Unit has.
     */
    int currentAvailableActions;

    /**
     * Creates a new unit using a new sprite.
     */
    Unit(PlayerID ownerID);

    /**
     * Creates a new unit given its sprite.
     */
    Unit(FMAW::Sprite sprite);

    /**
     * Creates a new unit given its sprite and owner.
     */
    Unit(FMAW::Sprite sprite, PlayerID ownerID);

    virtual void update();

    /**
     * Returns the movement capacity of this Unit.
     * @return Movement capacity of this Unit.
     */
    int getMovementCapacity();

    /**
     * Resets the internal counter of available actions.
     */
    void resetAvailableActions();

    /**
     * Decreases the internal counter of available actions.
     */
    void decreaseAvailableActions();

    /**
     * Returns whether this Unit has at least one available action or not.
     * @return Whether this Unit has at least oen available action or not.
     */
    bool hasAvailableActions();

    /**
     * Returns the ID of the owner of this unit.
     * @return ID of the owner of this unit.
     */
    PlayerID getOwner();
};

#endif