#ifndef WARRIOR_H
#define WARRIOR_H

#include "./FMAW.h"
#include "./constants.h"
#include "./unit.h"

//----------//------------------------------------------------------------------
//----------// Tile entries
//----------//------------------------------------------------------------------

// Framework will handle memory positions! :)
#define TILES_WARRIOR_1       0  // Warrior tiles (32x32 tile:  0 -> 15)
#define TILES_WARRIOR_2       1  // Warrior tiles (32x32 tile: 16 -> 31)
#define TILES_WARRIOR_3       2  // Warrior tiles (32x32 tile: 31 -> 47)

//----------//------------------------------------------------------------------
//----------// Other attributes
//----------//------------------------------------------------------------------

#define WARRIOR_HEIGHT        16

class Warrior : public Unit {
  protected:
    // ID of tile currently displayed.
    int currentTileID;
    // Palette of tile currently displayed.
    int currentTilePalette;
    // Tiles used to animate this Warrior.
    FMAW::Tile *tiles;

    virtual void init();
  public:
    /**
     * Creates a new Warrior using a new sprite.
     */
    Warrior(PlayerID ownerID): Unit(ownerID) {
        init();
    };

    /**
     * Creates a new Warrior given its sprite.
     */
    Warrior(FMAW::Sprite sprite, PlayerID ownerID): Unit(sprite, ownerID) {
        init();
    };

    virtual void update();

    /**
     * Resets position of this Warrior.
     */
    void reset();

    /**
     * Prints debug information about this warrior.
     */
    void print();
};

#endif