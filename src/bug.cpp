// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./bug.h"

#include <nds.h>

#include "./fmaw_macros.h"
#include "./fmaw_tile.h"

#include "./gfx_Bug_1.h"
#include "./gfx_Bug_2.h"
#include "./gfx_Bug_3.h"

#define SPRITES_IDLE_ANIMATION 4

void Bug::init() {
    this->tiles = reinterpret_cast<FMAW::Tile *>(
                      malloc(SPRITES_IDLE_ANIMATION * sizeof(FMAW::Tile)));

    FMAW::TileAttributes tile_1_attrib {
        gfx_Bug_1Tiles,
        gfx_Bug_1TilesLen,
        gfx_Bug_1Pal,
        gfx_Bug_1PalLen
    };
    FMAW::TileAttributes tile_2_attrib {
        gfx_Bug_2Tiles,
        gfx_Bug_2TilesLen,
        gfx_Bug_2Pal,
        gfx_Bug_2PalLen
    };
    FMAW::TileAttributes tile_3_attrib {
        gfx_Bug_3Tiles,
        gfx_Bug_3TilesLen,
        gfx_Bug_3Pal,
        gfx_Bug_3PalLen
    };

    FMAW::Tile tile_1(tile_1_attrib);
    FMAW::Tile tile_2(tile_2_attrib);
    FMAW::Tile tile_3(tile_3_attrib);

    this->tiles[0] = tile_1;
    this->tiles[1] = tile_2;
    this->tiles[2] = tile_3;
    this->tiles[3] = tile_2;

    this->currentTileID = 0;

    this->width = BUG_HEIGHT;
    this->height = BUG_HEIGHT;
    this->sprite.setSizeMode(FMAW::square32x32);
    this->sprite.setTile(this->tiles[this->currentTileID]);
    this->sprite.enable();
}

void Bug::update() {
    this->currentTileID += 1;
    this->currentTileID %= SPRITES_IDLE_ANIMATION;

    this->sprite.setTile(this->tiles[this->currentTileID]);
}

void Bug::reset() {
    this->x = 128 << 8;  // FixedReal(128);
    this->y = 64 << 8;   // FixedReal(64);
}
