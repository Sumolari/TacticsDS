#ifndef BUG_H
#define BUG_H

#include "./FMAW.h"

//----------//------------------------------------------------------------------
//----------// Tile entries
//----------//------------------------------------------------------------------

// Framework will handle memory positions! :)
#define TILES_BUG_1       0  // Bug tiles (32x32 tile:  0 -> 15)
#define TILES_BUG_2       1  // Bug tiles (32x32 tile: 16 -> 31)
#define TILES_BUG_3       2  // Bug tiles (32x32 tile: 31 -> 47)

//----------//------------------------------------------------------------------
//----------// Other attributes
//----------//------------------------------------------------------------------

#define BUG_HEIGHT        23

class Bug : public FMAW::Character {
protected:
    // ID of tile currently displayed.
    int currentTileID;
    // Palette of tile currently displayed.
    int currentTilePalette;
    // Tiles used to animate this bug.
    FMAW::Tile *tiles;

    virtual void init();
public:
    /**
     * Creates a new Bug using a new sprite.
     */
    Bug() {
        init();
    };

    /**
     * Creates a new Bug given its sprite.
     */
    Bug(FMAW::Sprite sprite): Character(sprite) {
        init();
    };

    virtual void update();

    /**
     * Resets position of this bug.
     */
    void reset();
};

#endif