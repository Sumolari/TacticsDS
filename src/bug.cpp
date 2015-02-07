// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./bug.h"

#include <nds.h>

void Bug::init() {
    time(&timer);
    this->tiles = malloc(4 * sizeof(int));
    this->tiles[0] = TILES_BUG_1;
    this->tiles[1] = TILES_BUG_2;
    this->tiles[2] = TILES_BUG_3;
    this->tiles[3] = TILES_BUG_2;
    this->palettes = malloc(4 * sizeof(int));
    this->palettes[0] = PAL_BUG_1;
    this->palettes[1] = PAL_BUG_2;
    this->palettes[2] = PAL_BUG_3;
    this->palettes[3] = PAL_BUG_2;
    this->currentTileID = 0;
}

void Bug::update() {
    time_t current;
    time(&current);

    this->sprite.setTile(TILES_BUG_1);
    this->sprite.setPalette(PAL_BUG_1);

    if (current > this->timer + 1000) {
        current = this->timer;
    }

    this->sprite.setTile(this->tiles[this->currentTileID]);
    this->sprite.setPalette(this->palettes[->currentTileID]);
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
