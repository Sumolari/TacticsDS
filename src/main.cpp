// Copyright 2015 FMAW

#include <sstream>
#include <cstdlib>
#include <string>

#include "./constants.h"

#include "./FMAW.h"  // Import our awesome framework!
#include "./memtrack.h"

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------

#include "./warrior.h"
#include "./knight.h"
#include "./sniper.h"

#include "./gfx_Base.h"
#include "./gfx_Bridge.h"
#include "./gfx_BridgeH.h"
#include "./gfx_Forest.h"
#include "./gfx_Grass.h"
#include "./gfx_Mountain.h"
#include "./gfx_River.h"
#include "./gfx_RiverH.h"
#include "./gfx_Castle.h"

#include "./gfx_Base_Fog.h"
#include "./gfx_Bridge_Fog.h"
#include "./gfx_BridgeH_Fog.h"
#include "./gfx_Forest_Fog.h"
#include "./gfx_Grass_Fog.h"
#include "./gfx_Mountain_Fog.h"
#include "./gfx_River_Fog.h"
#include "./gfx_RiverH_Fog.h"
#include "./gfx_Castle_Fog.h"

//------------------------------------------------------------------------------
// Background...
//------------------------------------------------------------------------------

#define BACKDROP_COLOR RGB8(190, 255, 255)

//------------------------------------------------------------------------------
// Game objects
//------------------------------------------------------------------------------

#include "./main_menu.h"
#include "./grid.h"
#include "./gridmap.h"
#include "./turnManager.h"
#include "./player.h"
#include "./player_ai.h"

Grid grid;
MainMenu menu;
Player *blue;
Player *red;
bool gameStarted;

int timesReported;

#define MAPS_COUNT 6

int selectedMap = 0;
std::string availableMaps[MAPS_COUNT] = {
    "defaultMap",
    "riverHood",
    "mistyMountain",
    "rivendel",
    "theFort",
    "troubleAhead"
};

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

    FMAW::TileAttributes gfx_RiverH_attributes {
        gfx_RiverHTiles,
        gfx_RiverHTilesLen,
        gfx_RiverHPal,
        gfx_RiverHPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile RiverH_tile(gfx_RiverH_attributes, River_tile);
    FMAW::printf("El fondo RiverH tiene ID=%d", RiverH_tile.ID);

    FMAW::TileAttributes gfx_BridgeH_attributes {
        gfx_BridgeHTiles,
        gfx_BridgeHTilesLen,
        gfx_BridgeHPal,
        gfx_BridgeHPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile BridgeH_tile(gfx_BridgeH_attributes, Bridge_tile);
    FMAW::printf("El fondo BridgeH tiene ID=%d", BridgeH_tile.ID);

    FMAW::TileAttributes gfx_Castle_attributes {
        gfx_CastleTiles,
        gfx_CastleTilesLen,
        gfx_CastlePal,
        gfx_CastlePalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Castle_tile(gfx_Castle_attributes);
    FMAW::printf("El fondo Castle tiene ID=%d", Castle_tile.ID);

    //------------------------------------------------------------------------//
    // SPACE RESERVED FOR FOG OF WAR TILES
    //------------------------------------------------------------------------//

    FMAW::TileAttributes gfx_Base_Fog_attributes {
        gfx_Base_FogTiles,
        gfx_Base_FogTilesLen,
        gfx_Base_FogPal,
        gfx_Base_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile base_Fog_tile(gfx_Base_Fog_attributes);
    FMAW::printf("El fondo Base_Fog tiene ID=%d", base_Fog_tile.ID);

    FMAW::TileAttributes gfx_Bridge_Fog_attributes {
        gfx_Bridge_FogTiles,
        gfx_Bridge_FogTilesLen,
        gfx_Bridge_FogPal,
        gfx_Bridge_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Bridge_Fog_tile(gfx_Bridge_Fog_attributes);
    FMAW::printf("El fondo Bridge_Fog tiene ID=%d", Bridge_Fog_tile.ID);

    FMAW::TileAttributes gfx_Forest_Fog_attributes {
        gfx_Forest_FogTiles,
        gfx_Forest_FogTilesLen,
        gfx_Forest_FogPal,
        gfx_Forest_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Forest_Fog_tile(gfx_Forest_Fog_attributes);
    FMAW::printf("El fondo Forest_Fog tiene ID=%d", Forest_Fog_tile.ID);

    FMAW::TileAttributes gfx_Grass_Fog_attributes {
        gfx_Grass_FogTiles,
        gfx_Grass_FogTilesLen,
        gfx_Grass_FogPal,
        gfx_Grass_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Grass_Fog_tile(gfx_Grass_Fog_attributes);
    FMAW::printf("El fondo Grass_Fog tiene ID=%d", Grass_Fog_tile.ID);

    FMAW::TileAttributes gfx_Mountain_Fog_attributes {
        gfx_Mountain_FogTiles,
        gfx_Mountain_FogTilesLen,
        gfx_Mountain_FogPal,
        gfx_Mountain_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Mountain_Fog_tile(gfx_Mountain_Fog_attributes);
    FMAW::printf("El fondo Mountain_Fog tiene ID=%d", Mountain_Fog_tile.ID);

    FMAW::TileAttributes gfx_River_Fog_attributes {
        gfx_River_FogTiles,
        gfx_River_FogTilesLen,
        gfx_River_FogPal,
        gfx_River_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile River_Fog_tile(gfx_River_Fog_attributes);
    FMAW::printf("El fondo River_Fog tiene ID=%d", River_Fog_tile.ID);

    FMAW::TileAttributes gfx_RiverH_Fog_attributes {
        gfx_RiverH_FogTiles,
        gfx_RiverH_FogTilesLen,
        gfx_RiverH_FogPal,
        gfx_RiverH_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile RiverH_Fog_tile(gfx_RiverH_Fog_attributes, River_Fog_tile);
    FMAW::printf("El fondo RiverH_Fog tiene ID=%d", RiverH_Fog_tile.ID);

    FMAW::TileAttributes gfx_BridgeH_Fog_attributes {
        gfx_BridgeH_FogTiles,
        gfx_BridgeH_FogTilesLen,
        gfx_BridgeH_FogPal,
        gfx_BridgeH_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile BridgeH_Fog_tile(gfx_BridgeH_Fog_attributes, Bridge_Fog_tile);
    FMAW::printf("El fondo BridgeH_Fog tiene ID=%d", BridgeH_Fog_tile.ID);

    FMAW::TileAttributes gfx_Castle_Fog_attributes {
        gfx_Castle_FogTiles,
        gfx_Castle_FogTilesLen,
        gfx_Castle_FogPal,
        gfx_Castle_FogPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenMain
    };
    FMAW::Tile Castle_Fog_tile(gfx_Castle_Fog_attributes);
    FMAW::printf("El fondo Castle_Fog tiene ID=%d", Castle_Fog_tile.ID);

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
    gameStarted = true; // Hack so we can change menu.

    auto finishTurnCallback = []() {
        grid.resetUnitMovements();
        FMAW::printf("Tocaría cambiar de turno!");
        TurnManager::finishTurn();
        grid.resetPickedUpCell();
        menu.adjustCurrentTile();
    };

    blue = new Player();
    TurnManager::addPlayer(blue);
    red = new Player();
    TurnManager::addPlayer(red);

    FMAW::init(update_graphics, update_logic);
    setupGraphics();

    grid.initCursor();
    grid.disableCursor();
    Unit::registerPalettes();
    GridMap::loadGridMap(availableMaps[selectedMap], &grid);

    auto loadSelectedMap = []() {
        grid.clearGridUnits();
        FMAW::Tile::releaseAllSpriteMemory();
        grid.initCursor();
        grid.disableCursor();
        Unit::registerPalettes();
        FMAW::printf("Loading map with ID=%d", selectedMap);
        GridMap::loadGridMap(availableMaps[selectedMap], &grid);
        grid.setFogOfWarMode(allVisible);
        // addSomeUnits();
        grid.enableSavingHistory(DEFAULT_SAVEGAME_FILE);
        //refresh menu
        menu.adjustCurrentTile();
    };

    int selectSoundID = FMAW::Sound::registerFX(
                            FMAW::Sound::effectWithSoundID(SFX_SELECT));

    auto leftArrowCallback = [loadSelectedMap, selectSoundID]() {
        if (menu.isInForeground()) {
            selectedMap += MAPS_COUNT - 1;
            selectedMap %= MAPS_COUNT;
            FMAW::Sound::playEffect(selectSoundID);
            loadSelectedMap();
        }
    };
    FMAW::Input::onButtonArrowLeftReleased(leftArrowCallback);

    auto rightArrowCallback = [loadSelectedMap, selectSoundID]() {
        if (menu.isInForeground()) {
            selectedMap += MAPS_COUNT + 1;
            selectedMap %= MAPS_COUNT;
            FMAW::Sound::playEffect(selectSoundID);
            loadSelectedMap();
        }
    };
    FMAW::Input::onButtonArrowRightReleased(rightArrowCallback);

    auto releaseB = [finishTurnCallback]() {
        if (menu.isInForeground() || grid.isInteractionEnabled()) return;
        finishTurnCallback();
        FMAW::printf("Has soltado la tecla B");
    };
    FMAW::Input::onButtonBReleased(releaseB);

    auto releaseStart = [selectSoundID]() {
        // Disable interaction is saved game is being played.
        if (grid.isPlayingSavedFile() || !gameStarted
                || TurnManager::AIPlaying()) return;

        FMAW::Sound::toggleBackgroundMusic();
        FMAW::Sound::playEffect(selectSoundID);

        if (menu.isInForeground()) {
            menu.makeBackground();
            grid.enqueueCallbacks();
        } else {
            menu.makeForeground();
            grid.dequeueCallbacks();
        }
        // MemTrack::TrackListMemoryUsage();
    };

    auto reportUsage = [](int ID) {
        FMAW::printf("Time: %d", timesReported++);
        MemTrack::TrackListMemoryUsage();
    };
    // FMAW::Timer::enqueue_function(reportUsage, 1000, true);

    FMAW::Input::onButtonStartReleased(releaseStart);

    auto newGameCallback = [loadSelectedMap, finishTurnCallback]() {
        gameStarted = true;
        FMAW::Sound::setBackgroundMusic(MOD_BSO);
        TurnManager::reset();
        delete blue;
        delete red;
        blue = new Player();
        TurnManager::addPlayer(blue);
        red = new PlayerAI(&grid, finishTurnCallback);
        red->print();
        TurnManager::addPlayer(red);

        FMAW::printf("Should start a new game!");
        loadSelectedMap();
        grid.setFogOfWarMode(fixedPlayerOne);
        grid.enableCursor();
        menu.makeBackground();
        grid.enqueueCallbacks();
    };

    auto loadGameCallback = [loadSelectedMap]() {
        gameStarted = false;
        FMAW::Sound::setBackgroundMusic(MOD_BSO);
        menu.makeBackground();
        FMAW::printf("Should load a previous game!");
        auto callback = [&loadSelectedMap](bool success) {
            FMAW::printf("Played saved game: %d", success);
            if (success) {
                loadSelectedMap();
                grid.enableSavingHistory(DEFAULT_SAVEGAME_FILE);
            }
            menu.makeForeground();
        };
        grid.playSavedHistory(DEFAULT_SAVEGAME_FILE, callback);
    };

    auto versusCallback = [loadSelectedMap]() {
        gameStarted = true;
        FMAW::Sound::setBackgroundMusic(MOD_BSO);
        TurnManager::reset();
        delete blue;
        delete red;
        blue = new Player();
        TurnManager::addPlayer(blue);
        red = new Player();
        red->print();
        TurnManager::addPlayer(red);

        FMAW::printf("Should start a new versus game!");
        loadSelectedMap();
        grid.setFogOfWarMode(enabled);
        grid.enableCursor();
        menu.makeBackground();
        grid.enqueueCallbacks();
    };

    menu.newGameCallback = newGameCallback;
    menu.loadGameCallback = loadGameCallback;
    menu.versusCallback = versusCallback;

    int victorySoundID = FMAW::Sound::registerFX(
                             FMAW::Sound::effectWithSoundID(SFX_WIN));

    auto gameOverCallback = [victorySoundID](int winner) {
        FMAW::printf("Winner is %d!", winner);
        TurnManager::setWinner(winner);
        menu.adjustCurrentTile();
        FMAW::Sound::stopBackgroundMusic();
        FMAW::Sound::playEffect(victorySoundID);
    };
    grid.gameOverCallback = gameOverCallback;

    menu.init();
    grid.enqueueCallbacks();
    grid.renderBackground();
    if (!grid.enableSavingHistory(DEFAULT_SAVEGAME_FILE)) {
        FMAW::printf("ERROR when trying to write file");
    }

    FMAW::Sound::pauseBackgroundMusic();

    releaseStart();

    gameStarted = false;

    FMAW::start();

    return 0;
}
