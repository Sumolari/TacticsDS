// Copyright 2015 FMAW

#include "./main_menu.h"

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------

#include "./gfx_logo.h"
#include "./gfx_main_menu.h"
#include "./gfx_main_menu_new_game.h"
#include "./gfx_main_menu_load_game.h"
#include "./gfx_main_menu_versus.h"

//------------------------------------------------------------------------------
// Main Menu options
//------------------------------------------------------------------------------

/**
 * ID of the Main Menu option that starts a new game.
 */
#define MAIN_MENU_OPTION_NEW_GAME    0

/**
 * ID of the Main Menu option that loads game.
 */
#define MAIN_MENU_OPTION_LOAD_GAME   1

/**
 * ID of the Main Menu option that starts a new versus.
 */
#define MAIN_MENU_OPTION_VERSUS_GAME 2

/**
 * AMmount of options available in the main menu.
 */
#define MAIN_MENU_NUM_OPTIONS        3

//------------------------------------------------------------------------------
// Main Menu
//------------------------------------------------------------------------------

MainMenu::MainMenu():
    menuCurrentlyOnForegroundScreen(false),
    menuChangedBackgroundTile(true),
    touchCallbackID(-1),
    upArrowCallbackID(-1),
    downArrowCallbackID(-1),
    aButtonCallbackID(-1),
    currentlySelectedOption(MAIN_MENU_OPTION_NEW_GAME),
    background(FMAW::Background(4)),
    logo_attributes(FMAW::TileAttributes(
                        gfx_logoTiles,
                        gfx_logoTilesLen,
                        gfx_logoPal,
                        gfx_logoPalLen,
                        FMAW::TypeBackground,
                        FMAW::ScreenSub)),
    main_menu_attributes(FMAW::TileAttributes(
                             gfx_main_menuTiles,
                             gfx_main_menuTilesLen,
                             gfx_main_menuPal,
                             gfx_main_menuPalLen,
                             FMAW::TypeBackground,
                             FMAW::ScreenSub)),
    main_menu_new_game_attributes(FMAW::TileAttributes(
                                      gfx_main_menu_new_gameTiles,
                                      gfx_main_menu_new_gameTilesLen,
                                      gfx_main_menu_new_gamePal,
                                      gfx_main_menu_new_gamePalLen,
                                      FMAW::TypeBackground,
                                      FMAW::ScreenSub)),
    main_menu_load_game_attributes(FMAW::TileAttributes(
                                       gfx_main_menu_load_gameTiles,
                                       gfx_main_menu_load_gameTilesLen,
                                       gfx_main_menu_load_gamePal,
                                       gfx_main_menu_load_gamePalLen,
                                       FMAW::TypeBackground,
                                       FMAW::ScreenSub)),
    main_menu_versus_attributes(FMAW::TileAttributes(
                                    gfx_main_menu_versusTiles,
                                    gfx_main_menu_versusTilesLen,
                                    gfx_main_menu_versusPal,
                                    gfx_main_menu_versusPalLen,
                                    FMAW::TypeBackground,
                                    FMAW::ScreenSub)),
    current_tile(FMAW::Tile(0)) {}

void MainMenu::init() {
    this->backgroundTileID = FMAW::Tile(logo_attributes).ID;
    this->adjustCurrentTile();
}

void MainMenu::adjustCurrentTile() {
    FMAW::printf("Current option is %d (%d) -> %d",
                 this->currentlySelectedOption,
                 this->isInForeground(),
                 this->current_tile.ID);

    if (this->isInForeground()) {
        switch (this->currentlySelectedOption) {
            case MAIN_MENU_OPTION_NEW_GAME:
                this->current_tile = FMAW::Tile(
                                         this->main_menu_new_game_attributes,
                                         this->backgroundTileID);
                break;
            case MAIN_MENU_OPTION_LOAD_GAME:
                this->current_tile = FMAW::Tile(
                                         this->main_menu_load_game_attributes,
                                         this->backgroundTileID);
                break;
            case MAIN_MENU_OPTION_VERSUS_GAME:
                this->current_tile = FMAW::Tile(
                                         this->main_menu_versus_attributes,
                                         this->backgroundTileID);
                break;
            default:
                this->current_tile = FMAW::Tile(this->main_menu_attributes,
                                                this->backgroundTileID);
                break;
        }
    } else {
        this->current_tile = FMAW::Tile(this->logo_attributes,
                                        this->backgroundTileID);
    }

    this->render();
}

void MainMenu::render() {
    if (this->menuChangedBackgroundTile) {
        FMAW::printf("I'll print tile with ID %d", this->current_tile.ID);
        this->background.setScreenBaseBlock(31);
        this->background.clearAllTiles();

        for (int id = 0; id < TOTAL_TILES; id++) {
            this->background.setTile(id, this->current_tile.imgMemory + id);
            this->background.setPalette(id, this->current_tile.palMemory);
        }

        this->menuChangedBackgroundTile = false;
    }
}

void MainMenu::makeForeground() {
    if (this->menuCurrentlyOnForegroundScreen) return;
    this->menuCurrentlyOnForegroundScreen = true;
    this->dequeueCallbacks();
    this->enqueueCallbacks();
    this->adjustCurrentTile();
    FMAW::swapScreens();
}

void MainMenu::makeBackground() {
    if (this->menuCurrentlyOnForegroundScreen) {
        this->menuCurrentlyOnForegroundScreen = false;
        this->dequeueCallbacks();
        this->adjustCurrentTile();
        FMAW::swapScreens();
    }
}

bool MainMenu::isInForeground() {
    return menuCurrentlyOnForegroundScreen;
}

void MainMenu::enqueueCallbacks() {
    if (this->touchCallbackID == -1) {
        auto touchCallback = [](int x, int y) {
            FMAW::printf("Touch detected at %d %d", x, y);
        };
        this->touchCallbackID = FMAW::Input::onTouchReleased(touchCallback);
    }
    if (this->upArrowCallbackID == -1) {
        auto upArrowCallback = [this]() {
            this->currentlySelectedOption--;
            if (this->currentlySelectedOption < 0) {
                this->currentlySelectedOption += MAIN_MENU_NUM_OPTIONS;
            }
            this->currentlySelectedOption %= MAIN_MENU_NUM_OPTIONS;
            this->menuChangedBackgroundTile = true;
            this->adjustCurrentTile();
            FMAW::printf("New selected option %d",
                         this->currentlySelectedOption);
        };
        this->upArrowCallbackID = FMAW::Input::onButtonArrowUpReleased(
                                      upArrowCallback);
    }
    if (this->downArrowCallbackID == -1) {
        auto downArrowCallback = [this]() {
            this->currentlySelectedOption++;
            this->currentlySelectedOption %= MAIN_MENU_NUM_OPTIONS;
            this->menuChangedBackgroundTile = true;
            this->adjustCurrentTile();
            FMAW::printf("New selected option %d",
                         this->currentlySelectedOption);
        };
        this->downArrowCallbackID = FMAW::Input::onButtonArrowDownReleased(
                                        downArrowCallback);
    }
    if (this->aButtonCallbackID == -1) {
        auto aButtonCallback = [this]() {
            FMAW::printf("Selected option %d",
                         this->currentlySelectedOption);
        };
        this->aButtonCallbackID = FMAW::Input::onButtonAReleased(
                                      aButtonCallback);
    }
}

void MainMenu::dequeueCallbacks() {
    if (this->touchCallbackID != -1)  {
        FMAW::Input::unregisterCallback(this->touchCallbackID);
        this->touchCallbackID = -1;
    }
    if (this->upArrowCallbackID != -1)  {
        FMAW::Input::unregisterCallback(this->upArrowCallbackID);
        this->upArrowCallbackID = -1;
    }
    if (this->downArrowCallbackID != -1)  {
        FMAW::Input::unregisterCallback(this->downArrowCallbackID);
        this->downArrowCallbackID = -1;
    }
    if (this->aButtonCallbackID != -1)  {
        FMAW::Input::unregisterCallback(this->aButtonCallbackID);
        this->aButtonCallbackID = -1;
    }
}
