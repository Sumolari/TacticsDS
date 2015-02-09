#ifndef BUG_H
#define BUG_H

#include "./FMAW.h"

#include <time.h>

//----------//------------------------------------------------------------------
//----------// Tile entries
//----------//------------------------------------------------------------------

#define TILES_BUG_1       0  // Bug tiles (32x32 tile:  0 -> 15)
#define TILES_BUG_2      16  // Bug tiles (32x32 tile: 16 -> 31)
#define TILES_BUG_3      32  // Bug tiles (32x32 tile: 31 -> 47)

//----------//------------------------------------------------------------------
//----------// Palette entries
//----------//------------------------------------------------------------------

#define PAL_BUG_1         0  // Ball palette (entry 0 -> 15)
#define PAL_BUG_2         1  // Ball palette (entry 16 -> 31)
#define PAL_BUG_3         2  // Ball palette (entry 32 -> 47)

//----------//------------------------------------------------------------------
//----------// Other attributes
//----------//------------------------------------------------------------------

#define BUG_HEIGHT        23

class Bug {
    // Last time bug changed sprite.
    time_t timer;
    // ID of tile currently displayed.
    int currentTileID;
    // Palette of tile currently displayed.
    int currentTilePalette;
    // Tiles used to animate this bug.
    int *tiles;
    // Palettes used to animate this bug.
    int *palettes;

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