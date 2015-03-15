// Copyright 2015 FMAW

#include <sstream>
#include <cstdlib>

#include "./constants.h"

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

    FMAW::init(update_graphics, update_logic);
    setupGraphics();

    grid.initCursor();

    GridMap::loadDefaultGridMap(&grid);

    auto addSomeUnits = [&blue, &red]() {
        Warrior *warriorA = new Warrior(blue.getID());
        Warrior *warriorB = new Warrior(red.getID());

        Warrior *warriorC = new Warrior(blue.getID());
        Warrior *warriorD = new Warrior(blue.getID());
        Warrior *warriorE = new Warrior(blue.getID());
        Warrior *warriorF = new Warrior(blue.getID());
        Warrior *warriorG = new Warrior(blue.getID());
        /*
        Warrior *warriorH = new Warrior(blue.getID());
        Warrior *warriorI = new Warrior(blue.getID());
        Warrior *warriorJ = new Warrior(blue.getID());
        Warrior *warriorK = new Warrior(blue.getID());
        Warrior *warriorL = new Warrior(blue.getID());
        */

        grid.cellAtIndexPath({0, 0})->setCharacter(warriorA);
        grid.cellAtIndexPath({4, 2})->setCharacter(warriorB);

        grid.cellAtIndexPath({0, 1})->setCharacter(warriorC);
        grid.cellAtIndexPath({0, 2})->setCharacter(warriorD);
        grid.cellAtIndexPath({0, 3})->setCharacter(warriorE);
        grid.cellAtIndexPath({0, 4})->setCharacter(warriorF);
        grid.cellAtIndexPath({0, 5})->setCharacter(warriorG);
        /*
        grid.cellAtIndexPath({1, 0})->setCharacter(warriorH);
        grid.cellAtIndexPath({1, 1})->setCharacter(warriorI);
        grid.cellAtIndexPath({1, 2})->setCharacter(warriorJ);
        grid.cellAtIndexPath({1, 3})->setCharacter(warriorK);
        grid.cellAtIndexPath({1, 4})->setCharacter(warriorL);
        */

        grid.resetUnitMovements();
    };

    auto releaseB = []() {
        if (menu.isInForeground()) return;

        grid.resetUnitMovements();
        FMAW::printf("Tocaría cambiar de turno!");
        grid.resetPickedUpCell();
        TurnManager::finishTurn();
        menu.adjustCurrentTile();
        FMAW::printf("Has soltado la tecla B");
    };
    FMAW::Input::onButtonBReleased(releaseB);

    auto releaseStart = []() {
        // Disable interaction is saved game is being played.
        if (grid.isPlayingSavedFile()) return;

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

    auto newGameCallback = []() {
        FMAW::printf("Should start a new game!");
    };

    auto loadGameCallback = [&addSomeUnits]() {
        menu.makeBackground();
        FMAW::printf("Should load a previous game!");
        auto callback = [&addSomeUnits](bool success) {
            FMAW::Tile::releaseAllSpriteMemory();
            FMAW::printf("Played saved game: %d", success);
            grid.initCursor();
            grid.clearGridUnits();
            addSomeUnits();
            menu.makeForeground();
        };
        grid.playSavedHistory(DEFAULT_SAVEGAME_FILE, callback);
    };

    auto versusCallback = []() {
        FMAW::printf("Should start a new versus game!");
    };

    menu.newGameCallback = newGameCallback;
    menu.loadGameCallback = loadGameCallback;
    menu.versusCallback = versusCallback;

    addSomeUnits();

    menu.init();
    grid.enqueueCallbacks();
    grid.renderBackground();
    if (!grid.enableSavingHistory(DEFAULT_SAVEGAME_FILE)) {
        FMAW::printf("ERROR when trying to write file");
    }

    FMAW::start();

    return 0;
}
