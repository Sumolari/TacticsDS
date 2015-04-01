#ifndef KNIGHT_H
#define KNIGHT_H

#include "./FMAW.h"
#include "./constants.h"
#include "./unit.h"

//----------//------------------------------------------------------------------
//----------// Tile entries
//----------//------------------------------------------------------------------

// Framework will handle memory positions! :)
#define TILES_KNIGHT_1       0  // Knight tiles (32x32 tile:  0 -> 15)
#define TILES_KNIGHT_2       1  // Knight tiles (32x32 tile: 16 -> 31)
#define TILES_KNIGHT_3       2  // Knight tiles (32x32 tile: 31 -> 47)

//----------//------------------------------------------------------------------
//----------// Other attributes
//----------//------------------------------------------------------------------

#define KNIGHT_HEIGHT        16

class Knight : public Unit {
  private:
    // Palettes used to draw this Warrior.
    static FMAW::Tile paletteBlue;
    static FMAW::Tile paletteRed;
  protected:
    // ID of tile currently displayed.
    int currentTileID;
    // Palette of tile currently displayed.
    int currentTilePalette;
    // Tiles used to animate this Knight.
    FMAW::TileAttributes **tiles;
    // Tile being used by this Knight.
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
     * Creates a new Knight using a new sprite.
     */
    explicit Knight(PlayerID ownerID): Unit(ownerID) {
        init();
    };

    /**
     * Creates a new Knight given its sprite.
     */
    explicit Knight(FMAW::Sprite sprite, PlayerID ownerID): Unit(sprite, ownerID) {
        init();
    };

    virtual void update();

    virtual void update_freq();

    /**
     * Resets position of this Knight.
     */
    void reset();

    /**
     * Prints debug information about this Knight.
     */
    void print();

    virtual ~Knight();
};

#endif
