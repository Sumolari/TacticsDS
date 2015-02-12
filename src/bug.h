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

class Bug {
    // Last time bug changed sprite.
    unsigned int timer;
    // ID of tile currently displayed.
    int currentTileID;
    // Palette of tile currently displayed.
    int currentTilePalette;
    // Tiles used to animate this bug.
    FMAW::Tile *tiles;

    /**
     * Initializes this bug.
     */
    void init();
public:
    // X coordinate.
    FixedReal x;
    // Y coordinate.
    FixedReal y;
    // Sprite of this bug.
    FMAW::Sprite sprite;

    /**
     * Creates a new ball using a new sprite.
     */
    Bug(): sprite(FMAW::Sprite()) {
        init();
    };

    /**
     * Creates a new ball given its sprite.
     */
    Bug(FMAW::Sprite sprite): sprite(sprite) {
        init();
    };

    /**
     * Updates this ball's position based on its velocity.
     */
    void update();

    /**
     * Renders this ball in given frame.
     * @param camera_x [description]
     * @param camera_y [description]
     */
    void render(int camera_x, int camera_y);

    /**
     * Displays information about this ball.
     */
    void print();
};

#endif