// Copyright 2015 FMAW

#include <sstream>
#include <cstdlib>
#include <fat.h>
#include <nds.h>

#include "./FMAW.h"  // Import our awesome framework!

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------

#include "./warrior.h"

#include "./gfx_brick.h"
#include "./gfx_gradient.h"

#include "./gfx_black.h"
#include "./gfx_blank.h"

#include "./gfx_Base.h"
#include "./gfx_Bridge.h"
#include "./gfx_Forest.h"
#include "./gfx_Grass.h"
#include "./gfx_Mountain.h"
#include "./gfx_River.h"

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

//------------------------------------------------------------------------------
// Game objects
//------------------------------------------------------------------------------

#include "./grid.h"
#include "./gridmap.h"

Grid grid;

FMAW::FixedReal g_camera_x;
FMAW::FixedReal g_camera_y;

//------------------------------------------------------------------------------
// Main code section
//------------------------------------------------------------------------------

/**
 * Sets up graphics.
 * Calling this method will require to reinitialize all sprites!
 */
void setupGraphics(void) {
    FMAW::TileAttributes blank_tile_attributes {
        gfx_blankTiles,
        gfx_blankTilesLen,
        gfx_blankPal,
        gfx_blankPalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile blank_tile(blank_tile_attributes);

    FMAW::TileAttributes black_tile_attributes {
        gfx_blackTiles,
        gfx_blackTilesLen,
        gfx_blackPal,
        gfx_blackPalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile black_tile(black_tile_attributes);
    FMAW::printf("El fondo negro tiene ID=%d", black_tile.ID);

    FMAW::TileAttributes brick_tile_attributes {
        gfx_brickTiles,
        gfx_brickTilesLen,
        gfx_brickPal,
        gfx_brickPalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile brick_tile(brick_tile_attributes);
    FMAW::printf("El fondo de ladrillo tiene ID=%d", brick_tile.ID);

    //------------------------------------------------------------------------//

    FMAW::TileAttributes gfx_Base_attributes {
        gfx_BaseTiles,
        gfx_BaseTilesLen,
        gfx_BasePal,
        gfx_BasePalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile base_tile(gfx_Base_attributes);
    FMAW::printf("El fondo Base tiene ID=%d", base_tile.ID);

    FMAW::TileAttributes gfx_Bridge_attributes {
        gfx_BridgeTiles,
        gfx_BridgeTilesLen,
        gfx_BridgePal,
        gfx_BridgePalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile Bridge_tile(gfx_Bridge_attributes);
    FMAW::printf("El fondo Bridge tiene ID=%d", Bridge_tile.ID);

    FMAW::TileAttributes gfx_Forest_attributes {
        gfx_ForestTiles,
        gfx_ForestTilesLen,
        gfx_ForestPal,
        gfx_ForestPalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile Forest_tile(gfx_Forest_attributes);
    FMAW::printf("El fondo Forest tiene ID=%d", Forest_tile.ID);

    FMAW::TileAttributes gfx_Grass_attributes {
        gfx_GrassTiles,
        gfx_GrassTilesLen,
        gfx_GrassPal,
        gfx_GrassPalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile Grass_tile(gfx_Grass_attributes);
    FMAW::printf("El fondo Grass tiene ID=%d", Grass_tile.ID);

    FMAW::TileAttributes gfx_Mountain_attributes {
        gfx_MountainTiles,
        gfx_MountainTilesLen,
        gfx_MountainPal,
        gfx_MountainPalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile Mountain_tile(gfx_Mountain_attributes);
    FMAW::printf("El fondo Mountain tiene ID=%d", Mountain_tile.ID);

    FMAW::TileAttributes gfx_River_attributes {
        gfx_RiverTiles,
        gfx_RiverTilesLen,
        gfx_RiverPal,
        gfx_RiverPalLen,
        FMAW::TypeBackground
    };
    FMAW::Tile River_tile(gfx_River_attributes);
    FMAW::printf("El fondo River tiene ID=%d", River_tile.ID);

    //------------------------------------------------------------------------//

    // Set backdrop color.
    FMAW::setBackgroundColor(BACKDROP_COLOR);

    FMAW::Background bgBricks(0);
    bgBricks.setScreenBaseBlock(2);

    FMAW::Background(1).setScreenBaseBlock(3);
    FMAW::Background(2).setScreenBaseBlock(4);
    FMAW::Background(3).setScreenBaseBlock(5);

    // Clear entire bricks' tilemap and gradient's tilemap to zero
    bgBricks.clearAllTiles();

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
    // bgBricks.setVerticalOffset(112);

	GridMap::loadDefaultGridMap( grid );
    grid.renderBackground();
}

void update_camera() { }

void update_logic() {
    FMAW::Input::check();
    FMAW::Timer::check();
    update_camera();
}

void update_graphics() {
    FMAW::Camera::setHorizontalOffset(g_camera_x);
    grid.renderCharacters();
}

int main(void) {
	consoleDemoInit();
	fatInitDefault();
    FMAW::init();
    setupGraphics();

    auto pulsaFlechaIzquierda = []() {
        FMAW::printf("Has pulsado la flecha izquierda");
    };
    FMAW::Input::onButtonArrowLeftPressed(pulsaFlechaIzquierda);

    auto mantenFlechaIzquierda = []() {
        FMAW::printf("Mantienes la flecha izquierda pulsada");
    };
    FMAW::Input::whileButtonArrowLeftPressed(mantenFlechaIzquierda);

    auto sueltaFlechaIzquierda = []() {
        FMAW::printf("Has soltado la flecha izquierda");
    };
    FMAW::Input::onButtonArrowLeftReleased(sueltaFlechaIzquierda);

    //grid.cellAtIndexPath({3, 6})->setBackgroundType(CellBGMountain);

    //grid.cellAtIndexPath({4, 4})->setBackgroundType(CellBGRiver);

    Warrior warrior;
    grid.cellAtIndexPath({0, 0})->setCharacter(&warrior);

    auto func = [&warrior](int ID) {
        warrior.update();
    };

    FMAW::Timer::enqueue_function(func, 200, true);

    int prev_col = 0;
    int prev_row = 0;

    auto move_warrior = [&prev_col, &prev_row, &warrior](int ID) {
        int new_col = (prev_col < grid.numCols()) ? prev_col + 1 : 0;
        int new_row = (new_col == 0) ? prev_row + 1 : prev_row;

        FMAW::printf("La guerrera se mueve de %d %d a %d %d!",
                     prev_row, prev_col,
                     new_row, new_col);
        grid.moveCharacterFromCellToCell({prev_row, prev_col}, {new_row, new_col}, 100);

        prev_col = new_col;
        prev_row = new_row;
    };

    FMAW::Timer::enqueue_function(move_warrior, 5000, true);

    grid.renderBackground();

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
