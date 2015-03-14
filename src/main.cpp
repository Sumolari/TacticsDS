// Copyright 2015 FMAW

#ifdef NDS

#include <fat.h>
#include <nds.h>

#include <sstream>
#include <cstdlib>

#include "./FMAW.h"  // Import our awesome framework!
#include "./memtrack.h"

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

#include "./main_menu.h"
#include "./grid.h"
#include "./gridmap.h"
#include "./turnManager.h"

Grid grid;
MainMenu menu;

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
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile blank_tile(blank_tile_attributes);

    FMAW::TileAttributes black_tile_attributes {
        gfx_blackTiles,
        gfx_blackTilesLen,
        gfx_blackPal,
        gfx_blackPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile black_tile(black_tile_attributes);
    FMAW::printf("El fondo negro tiene ID=%d", black_tile.ID);

    FMAW::TileAttributes brick_tile_attributes {
        gfx_brickTiles,
        gfx_brickTilesLen,
        gfx_brickPal,
        gfx_brickPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile brick_tile(brick_tile_attributes);
    FMAW::printf("El fondo de ladrillo tiene ID=%d", brick_tile.ID);

    //------------------------------------------------------------------------//

    FMAW::TileAttributes gfx_Base_attributes {
        gfx_BaseTiles,
        gfx_BaseTilesLen,
        gfx_BasePal,
        gfx_BasePalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile base_tile(gfx_Base_attributes);
    FMAW::printf("El fondo Base tiene ID=%d", base_tile.ID);

    FMAW::TileAttributes gfx_Bridge_attributes {
        gfx_BridgeTiles,
        gfx_BridgeTilesLen,
        gfx_BridgePal,
        gfx_BridgePalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Bridge_tile(gfx_Bridge_attributes);
    FMAW::printf("El fondo Bridge tiene ID=%d", Bridge_tile.ID);

    FMAW::TileAttributes gfx_Forest_attributes {
        gfx_ForestTiles,
        gfx_ForestTilesLen,
        gfx_ForestPal,
        gfx_ForestPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Forest_tile(gfx_Forest_attributes);
    FMAW::printf("El fondo Forest tiene ID=%d", Forest_tile.ID);

    FMAW::TileAttributes gfx_Grass_attributes {
        gfx_GrassTiles,
        gfx_GrassTilesLen,
        gfx_GrassPal,
        gfx_GrassPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Grass_tile(gfx_Grass_attributes);
    FMAW::printf("El fondo Grass tiene ID=%d", Grass_tile.ID);

    FMAW::TileAttributes gfx_Mountain_attributes {
        gfx_MountainTiles,
        gfx_MountainTilesLen,
        gfx_MountainPal,
        gfx_MountainPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Mountain_tile(gfx_Mountain_attributes);
    FMAW::printf("El fondo Mountain tiene ID=%d", Mountain_tile.ID);

    FMAW::TileAttributes gfx_River_attributes {
        gfx_RiverTiles,
        gfx_RiverTilesLen,
        gfx_RiverPal,
        gfx_RiverPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile River_tile(gfx_River_attributes);
    FMAW::printf("El fondo River tiene ID=%d", River_tile.ID);

    //------------------------------------------------------------------------//

    // Set backdrop color.
    FMAW::setBackgroundColor(BACKDROP_COLOR);

    FMAW::Background(0).setScreenBaseBlock(2);
    FMAW::Background(1).setScreenBaseBlock(3);
    FMAW::Background(2).setScreenBaseBlock(4);
    FMAW::Background(3).setScreenBaseBlock(5);
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
    Player blue;
    TurnManager::addPlayer(&blue);
    Player red;
    TurnManager::addPlayer(&red);

    fatInitDefault();
    FMAW::init(update_graphics, update_logic);
    setupGraphics();

    grid.initCursor();

    GridMap::loadDefaultGridMap(grid);

    Warrior warriorA{blue.getID()}, warriorB{red.getID()};
    grid.cellAtIndexPath({0, 0})->setCharacter(&warriorA);
    warriorA.print();
    grid.cellAtIndexPath({4, 2})->setCharacter(&warriorB);

    auto func = [&warriorA, &warriorB](int ID) {
        warriorA.update();
        warriorB.update();
    };
    FMAW::Timer::enqueue_function(func, 200, true);

    auto releaseB = []() {
        grid.resetUnitMovements();
        FMAW::printf("Tocaría cambiar de turno!");
        grid.resetPickedUpCell();
        TurnManager::finishTurn();
        menu.adjustCurrentTile();
        FMAW::printf("Has soltado la tecla B");
    };
    FMAW::Input::onButtonBReleased(releaseB);

    auto releaseStart = []() {
        if (menu.isInForeground()) {
            menu.makeBackground();
            grid.enqueueCallbacks();
        } else {
            menu.makeForeground();
            grid.dequeueCallbacks();
        }
        // MemTrack::TrackListMemoryUsage();
    };
    FMAW::Input::onButtonStartReleased(releaseStart);

    menu.init();
    grid.resetUnitMovements();
    grid.enqueueCallbacks();
    grid.renderBackground();

    FMAW::start();

    return 0;
}

#endif
