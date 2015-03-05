// Copyright 2015 FMAW

#include "./main_menu.h"
#include "./FMAW.h"

#include "./gfx_main_menu.h"

namespace MainMenu {

bool menuCurrentlyOnForegroundScreen = false;
int touchCallbackID = -1;

auto touchCallback = [](int x, int y) {
    FMAW::printf("Touch detected at %d %d", x, y);
};

void render() {
    FMAW::TileAttributes background_tile_attributes {
        gfx_main_menuTiles,
        gfx_main_menuTilesLen,
        gfx_main_menuPal,
        gfx_main_menuPalLen,
        FMAW::TypeBackground,
        FMAW::ScreenSub
    };
    FMAW::Tile background_tile(background_tile_attributes);

    FMAW::Background menuBackground(4);

    menuBackground.setScreenBaseBlock(31);
    menuBackground.clearAllTiles();

    FMAW::printf("River background at %p", FMAW::Tile(8).imgMemory);
    FMAW::printf("MainMenu background at %p", background_tile.imgMemory);
    menuBackground.print();
    FMAW::Background(0).print();
    FMAW::printf("Hay %d tiles", gfx_main_menuTilesLen);

    /*
    for (int i = 0; i < this->tiles.size(); ++i) {
        this->background.setTile(
            this->tiles[i],
            FMAW::Tile(this->backgroundType).imgMemory + i);
        this->background.setPalette(
            this->tiles[i],
            FMAW::Tile(this->backgroundType).palMemory);
    }
    */

    for (int id = 0; id < TOTAL_TILES; id++) {
        // menuBackground.setTile(id, FMAW::Tile(8));
        menuBackground.setTile(id, background_tile.imgMemory + id);
        menuBackground.setPalette(id, background_tile.palMemory);
    }
}

void makeMenuForeground() {
    if (menuCurrentlyOnForegroundScreen) return;
    FMAW::swapScreens();
}

void makeMenuBackground() {
    if (menuCurrentlyOnForegroundScreen) FMAW::swapScreens();
}

void enqueueMenuCallbacks() {
    if (touchCallbackID == -1) {
        touchCallbackID = FMAW::Input::onTouchReleased(touchCallback);
    }
}

void dequeueMenuCallbacks() {
    FMAW::Input::unregisterCallback(touchCallbackID);
    touchCallbackID = -1;
}

}  // namespace MainMenu
