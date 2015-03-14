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

    /**
     * Amount of movement points that this Unit has available.
     */
    int movementCapacity;

    virtual void init();
  public:
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
     * Returns the ID of the owner of this unit.
     * @return ID of the owner of this unit.
     */
    PlayerID getOwner();
};

#endif