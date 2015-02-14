// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include <nds.h>
#include <nds/debug.h>
#include <sstream>

#include "./FMAW.h"  // Import our awesome framework!

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------

#include "./gfx_brick.h"
#include "./gfx_gradient.h"

//------------------------------------------------------------------------------
// Background tile entries
//------------------------------------------------------------------------------

#define TILE_EMPTY     0  // Tile 0 = empty
#define TILE_BRICK     1  // Tile 1 = brick
#define TILE_GRADIENT  2  // Tile 2 = gradient

//------------------------------------------------------------------------------
// Background...
//------------------------------------------------------------------------------

//----------//------------------------------------------------------------------
//----------// Palette entries
//----------//------------------------------------------------------------------

#define PAL_BRICKS     0  // Brick palette (entry 0->15).
#define PAL_GRADIENT   1  // Gradient palette (entry 16->31).

#define BACKDROP_COLOR RGB8(190, 255, 255)

//----------//------------------------------------------------------------------
//----------// Screen base blocks pointed
//----------//------------------------------------------------------------------

#define bg0map    (reinterpret_cast<u16*>BG_MAP_RAM(1))
#define bg1map    (reinterpret_cast<u16*>BG_MAP_RAM(2))

//------------------------------------------------------------------------------
// Game objects
//------------------------------------------------------------------------------

#include "./bug.h"

Bug g_bug;

FixedReal g_camera_x;
FixedReal g_camera_y;

//------------------------------------------------------------------------------
// Main code section
//------------------------------------------------------------------------------

/**
 * Sets up graphics.
 * Calling this method will require to reinitialize all sprites!
 */
void setupGraphics(void) {
    // Generate the first blank tile by clearing it to zero.
    for (int n = 0; n < 16; n++)
        BG_GFX[n] = 0;

    FMAW::TileAttributes brick_attributes {
        gfx_brickTiles,
        gfx_brickTilesLen,
        gfx_brickPal,
        gfx_brickPalLen,
        FMAW::TypeBackground
    };
    FMAW::TileAttributes gradient_attributes {
        gfx_gradientTiles,
        gfx_gradientTilesLen,
        gfx_gradientPal,
        gfx_gradientPalLen,
        FMAW::TypeBackground
    };

    FMAW::Tile brick_tile(brick_attributes);
    FMAW::Tile gradient_tile(gradient_attributes);

    // Set backdrop color.
    FMAW::setBackgroundColor(BACKDROP_COLOR);

    FMAW::Background bgBricks(0);
    bgBricks.setScreenBaseBlock(1);

    FMAW::Background bgGradient(1);
    bgGradient.setScreenBaseBlock(2);

    // Clear entire bricks' tilemap and gradient's tilemap to zero
    bgBricks.clearAllTiles();
    bgGradient.clearAllTiles();

    // Set tilemap entries for 6 first rows of background 0 (bricks).
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 32; x++) {
            int tile_id = x + y * 32;  // Product optimized at compile time!

            // Either odd columns of even rows or even columns of odd rows...
            // if (( x % 2 == 0 && y % 2 == 1 ) || (x % 2 == 1 && y % 2 == 0 ))
            if ((x & 1) ^ (y & 1))
                bgBricks.enableHorizontalFlip(tile_id);

            bgBricks.setTile(tile_id, brick_tile);
        }
    }
    // Did we say 6 first rows? We wanted 6 LAST rows!
    bgBricks.setVerticalOffset(112);

    // Set tilemap entries for 8 first rows of background 1 (gradient).
    for (int y = 0; y < 8; y++) {
        int tile_index = gradient_tile.imgMemory + y;
        int y32 = y * 32;

        for (int x = 0; x < 32; x++) {
            int tile_id = x + y32;
            bgGradient.setTile(tile_id, tile_index);
            bgGradient.setPalette(tile_id, gradient_tile.palMemory);
        }
    }

    // Enable alpha blending of background 1.
    // My guess: BLEND_DST_BACKDROP is the 14th bit at 1, BLEND_SRC_BG1 is the
    //           2nd bit at 1 and BLEND_ALPHA are bits 8th and 7th at 10.
    //           BLEND_DST_BACKDROP 0010000000000000
    //           BLEND_SRC_BG1      0000000000000010
    //           BLEND_ALPHA        0000000010000000
    //           -----------------------------------
    //                              0010000010000010
    REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG1 | BLEND_DST_BACKDROP;
    REG_BLDALPHA = (4) + (16 << 8);  // This is computed at compile time.

    g_bug = Bug(FMAW::Sprite(0));
}

void process_input() { }

void update_camera() { }

void update_logic() {
    process_input();
    FMAW::Timer::check();
    update_camera();
}

void update_graphics() {
    g_bug.render(g_camera_x >> 8, g_camera_y >> 8);

    REG_BG0HOFS = g_camera_x >> 8;  // REG_BG0HOFS = g_camera_x.toInt();
}

int main(void) {
    FMAW::init();
    setupGraphics();

    auto func = [](int ID) {
        g_bug.update();
    };

    FMAW::Timer::enqueue_function(func, 200, true);

    while (1) {
        // Rendering period:
        // Update game objects.
        update_logic();

        // Wait for the vblank period.
        swiWaitForVBlank();

        // VBlank period: (safe yo modify graphics)
        // Move the graphics around.
        update_graphics();
    }

    return 0;
}
