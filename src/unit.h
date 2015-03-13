#ifndef UNIT_H
#define UNIT_H

#include "./FMAW.h"

class Unit : public FMAW::Character {
  protected:
    // ID of player who owns this unit.
    int ownerID;

    virtual void init();
  public:
    /**
     * Creates a new unit using a new sprite.
     */
    Unit(int ownerID);

    /**
     * Creates a new unit given its sprite.
     */
    Unit(FMAW::Sprite sprite);

    /**
     * Creates a new unit given its sprite and owner.
     */
    Unit(FMAW::Sprite sprite, int ownerID);

    virtual void update();

    /**
     * Returns the ID of the owner of this unit.
     * @return ID of the owner of this unit.
     */
    int getOwner();
};

#endif