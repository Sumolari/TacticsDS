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
  private:
    // Palettes used to draw this Warrior.
    static FMAW::Tile paletteBlue;
    static FMAW::Tile paletteRed;
  protected:
    // ID of tile currently displayed.
    int currentTileID;
    // Palette of tile currently displayed.
    int currentTilePalette;
    // Tiles used to animate this Warrior.
    FMAW::TileAttributes **tiles;
    // Tile being used by this warrior.
    FMAW::Tile *tile;
    // ID of the update callback.
    int updateID;

    virtual void init();
  public:
    /**
     * Registers pelettes for this unit.
     */
    static void registerPalettes();

    /**
     * Creates a new Warrior using a new sprite.
     */
    explicit Warrior(PlayerID ownerID): Unit(ownerID) {
        init();
    };

    /**
     * Creates a new Warrior given its sprite.
     */
    explicit Warrior(FMAW::Sprite sprite, PlayerID ownerID): Unit(sprite, ownerID) {
        init();
    };

    virtual void update();

    virtual void update_freq();

    /**
     * Resets position of this Warrior.
     */
    void reset();

    /**
     * Prints debug information about this warrior.
     */
    void print();

    virtual ~Warrior();
};

#endif
