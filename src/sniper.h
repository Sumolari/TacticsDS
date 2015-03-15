#ifndef SNIPER_H
#define SNIPER_H

#include "./FMAW.h"
#include "./constants.h"
#include "./unit.h"

//----------//------------------------------------------------------------------
//----------// Tile entries
//----------//------------------------------------------------------------------

// Framework will handle memory positions! :)
#define TILES_SNIPER_1       0  // Sniper tiles (32x32 tile:  0 -> 15)
#define TILES_SNIPER_2       1  // Sniper tiles (32x32 tile: 16 -> 31)
#define TILES_SNIPER_3       2  // Sniper tiles (32x32 tile: 31 -> 47)

//----------//------------------------------------------------------------------
//----------// Other attributes
//----------//------------------------------------------------------------------

#define SNIPER_HEIGHT        16

class Sniper : public Unit {
  protected:
    // ID of tile currently displayed.
    int currentTileID;
    // Palette of tile currently displayed.
    int currentTilePalette;
    // Tiles used to animate this Sniper.
    FMAW::TileAttributes **tiles;
    // Tile being used by this Sniper.
    FMAW::Tile *tile;
    // ID of the update callback.
    int updateID;

    virtual void init();
  public:
    /**
     * Creates a new Sniper using a new sprite.
     */
    explicit Sniper(PlayerID ownerID): Unit(ownerID) {
        init();
    };

    /**
     * Creates a new Sniper given its sprite.
     */
    explicit Sniper(FMAW::Sprite sprite, PlayerID ownerID): Unit(sprite, ownerID) {
        init();
    };

    virtual void update();

    /**
     * Resets position of this Sniper.
     */
    void reset();

    /**
     * Prints debug information about this Sniper.
     */
    void print();

    virtual ~Sniper();
};

#endif
