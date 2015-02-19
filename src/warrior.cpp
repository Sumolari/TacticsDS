// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./warrior.h"

#include "./fmaw_tile.h"

#include "./swordmaster_female_1.h"
#include "./swordmaster_female_2.h"
#include "./swordmaster_female_3.h"
#include "./swordmaster_female_4.h"

#define SPRITES_IDLE_ANIMATION 4

void Warrior::init() {
    this->reset();

    this->tiles = reinterpret_cast<FMAW::Tile *>(
                      malloc(SPRITES_IDLE_ANIMATION * sizeof(FMAW::Tile)));

    FMAW::TileAttributes tile_1_attrib {
        swordmaster_female_1Tiles,
        swordmaster_female_1TilesLen,
        swordmaster_female_1Pal,
        swordmaster_female_1PalLen,
        FMAW::TypeSprite
    };
    FMAW::TileAttributes tile_2_attrib {
        swordmaster_female_2Tiles,
        swordmaster_female_2TilesLen,
        swordmaster_female_2Pal,
        swordmaster_female_2PalLen,
        FMAW::TypeSprite
    };
    FMAW::TileAttributes tile_3_attrib {
        swordmaster_female_3Tiles,
        swordmaster_female_3TilesLen,
        swordmaster_female_3Pal,
        swordmaster_female_3PalLen,
        FMAW::TypeSprite
    };
    FMAW::TileAttributes tile_4_attrib {
        swordmaster_female_4Tiles,
        swordmaster_female_4TilesLen,
        swordmaster_female_4Pal,
        swordmaster_female_4PalLen,
        FMAW::TypeSprite
    };

    FMAW::Tile tile_1(tile_1_attrib);
    FMAW::Tile tile_2(tile_2_attrib);
    FMAW::Tile tile_3(tile_3_attrib);
    FMAW::Tile tile_4(tile_4_attrib);

    this->tiles[0] = tile_1;
    this->tiles[1] = tile_2;
    this->tiles[2] = tile_3;
    this->tiles[3] = tile_4;

    this->currentTileID = 0;

    this->width = WARRIOR_HEIGHT;
    this->height = WARRIOR_HEIGHT;
    this->sprite.setSizeMode(FMAW::square16x16);
    this->sprite.setTile(this->tiles[this->currentTileID]);
    this->sprite.enable();
}

void Warrior::update() {
    this->currentTileID += 1;
    this->currentTileID %= SPRITES_IDLE_ANIMATION;

    this->sprite.setTile(this->tiles[this->currentTileID]);
}

void Warrior::reset() {
    this->x = 128 << 8;  // FixedReal(128);
    this->y = 64 << 8;   // FixedReal(64);
}
