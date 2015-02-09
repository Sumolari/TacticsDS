// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./bug.h"

#include <nds.h>

#include "./fmaw_macros.h"

#include "./gfx_Bug_1.h"
#include "./gfx_Bug_2.h"
#include "./gfx_Bug_3.h"

#define SPRITES_IDLE_ANIMATION 4

void Bug::init() {
    time(&timer);
    this->tiles = reinterpret_cast<int *>(
                      malloc(SPRITES_IDLE_ANIMATION * sizeof(int)));
    this->tiles[0] = TILES_BUG_1;
    this->tiles[1] = TILES_BUG_2;
    this->tiles[2] = TILES_BUG_3;
    this->tiles[3] = TILES_BUG_2;
    this->palettes = reinterpret_cast<int *>(
                         malloc(SPRITES_IDLE_ANIMATION * sizeof(int)));
    this->palettes[0] = PAL_BUG_1;
    this->palettes[1] = PAL_BUG_2;
    this->palettes[2] = PAL_BUG_3;
    this->palettes[3] = PAL_BUG_2;
    this->currentTileID = 0;

    dmaCopyHalfWords(3, gfx_Bug_1Tiles, tile2objram(TILES_BUG_1),
                     gfx_Bug_1TilesLen);
    dmaCopyHalfWords(3, gfx_Bug_2Tiles, tile2objram(TILES_BUG_2),
                     gfx_Bug_2TilesLen);
    dmaCopyHalfWords(3, gfx_Bug_3Tiles, tile2objram(TILES_BUG_3),
                     gfx_Bug_3TilesLen);

    dmaCopyHalfWords(3, gfx_Bug_1Pal, pal2objram(PAL_BUG_1), gfx_Bug_1PalLen);
    dmaCopyHalfWords(3, gfx_Bug_2Pal, pal2objram(PAL_BUG_2), gfx_Bug_2PalLen);
    dmaCopyHalfWords(3, gfx_Bug_3Pal, pal2objram(PAL_BUG_3), gfx_Bug_3PalLen);

    this->currentTileID = 0;
}

void Bug::update() {
    time_t current;
    time(&current);

    if (current > this->timer + 1) {
        this->timer = current;
        this->currentTileID += 1;
        this->currentTileID %= SPRITES_IDLE_ANIMATION;
    }

    this->sprite.setTile(this->tiles[this->currentTileID]);
    this->sprite.setPalette(this->palettes[this->currentTileID]);
}

void Bug::render(int camera_x, int camera_y) {
    FixedReal x, y;
    x = ((this->x - BUG_HEIGHT) >> 8) - camera_x;
    y = ((this->y - BUG_HEIGHT) >> 8) - camera_y;

    if (x <= -16 || y <= -16 || x >= 256 || y >= 192) {
        this->sprite.disable();
        return;
    }

    this->sprite.setPosition(x, y);
    this->sprite.setSizeMode(FMAW::square32x32);
}

void Bug::print() {
    FMAW::printf("Bug using sprite:");
    this->sprite.print();
}
