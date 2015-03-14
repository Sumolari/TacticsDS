// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./warrior.h"

#include "./fmaw_tile.h"

#include "./swordmaster_female_1_blue.h"
#include "./swordmaster_female_2_blue.h"
#include "./swordmaster_female_3_blue.h"
#include "./swordmaster_female_4_blue.h"

#include "./swordmaster_female_1_red.h"
#include "./swordmaster_female_2_red.h"
#include "./swordmaster_female_3_red.h"
#include "./swordmaster_female_4_red.h"

#define SPRITES_IDLE_ANIMATION 4

void Warrior::init() {
    this->reset();

    this->tiles = reinterpret_cast<FMAW::Tile *>(
                      malloc(SPRITES_IDLE_ANIMATION * sizeof(FMAW::Tile)));

    FMAW::printf("This warrior has owner: %d", this->ownerID);

    //--------------------------------------------------------------------------
    // Decide proper tile based on current owner.
    //--------------------------------------------------------------------------

    auto swordmaster_female_1Tiles = (this->ownerID == 0) ?
                                     swordmaster_female_1_blueTiles :
                                     swordmaster_female_1_redTiles;
    auto swordmaster_female_1TilesLen = (this->ownerID == 0) ?
                                        swordmaster_female_1_blueTilesLen :
                                        swordmaster_female_1_redTilesLen;
    auto swordmaster_female_1Pal = (this->ownerID == 0) ?
                                   swordmaster_female_1_bluePal :
                                   swordmaster_female_1_redPal;
    auto swordmaster_female_1PalLen = (this->ownerID == 0) ?
                                      swordmaster_female_1_bluePalLen :
                                      swordmaster_female_1_redPalLen;

    auto swordmaster_female_2Tiles = (this->ownerID == 0) ?
                                     swordmaster_female_2_blueTiles :
                                     swordmaster_female_2_redTiles;
    auto swordmaster_female_2TilesLen = (this->ownerID == 0) ?
                                        swordmaster_female_2_blueTilesLen :
                                        swordmaster_female_2_redTilesLen;
    auto swordmaster_female_2Pal = (this->ownerID == 0) ?
                                   swordmaster_female_2_bluePal :
                                   swordmaster_female_2_redPal;
    auto swordmaster_female_2PalLen = (this->ownerID == 0) ?
                                      swordmaster_female_2_bluePalLen :
                                      swordmaster_female_2_redPalLen;

    auto swordmaster_female_3Tiles = (this->ownerID == 0) ?
                                     swordmaster_female_3_blueTiles :
                                     swordmaster_female_3_redTiles;
    auto swordmaster_female_3TilesLen = (this->ownerID == 0) ?
                                        swordmaster_female_3_blueTilesLen :
                                        swordmaster_female_3_redTilesLen;
    auto swordmaster_female_3Pal = (this->ownerID == 0) ?
                                   swordmaster_female_3_bluePal :
                                   swordmaster_female_3_redPal;
    auto swordmaster_female_3PalLen = (this->ownerID == 0) ?
                                      swordmaster_female_3_bluePalLen :
                                      swordmaster_female_3_redPalLen;

    auto swordmaster_female_4Tiles = (this->ownerID == 0) ?
                                     swordmaster_female_4_blueTiles :
                                     swordmaster_female_4_redTiles;
    auto swordmaster_female_4TilesLen = (this->ownerID == 0) ?
                                        swordmaster_female_4_blueTilesLen :
                                        swordmaster_female_4_redTilesLen;
    auto swordmaster_female_4Pal = (this->ownerID == 0) ?
                                   swordmaster_female_4_bluePal :
                                   swordmaster_female_4_redPal;
    auto swordmaster_female_4PalLen = (this->ownerID == 0) ?
                                      swordmaster_female_4_bluePalLen :
                                      swordmaster_female_4_redPalLen;

    //--------------------------------------------------------------------------
    // Load tile.
    //--------------------------------------------------------------------------

    FMAW::TileAttributes tile_1_attrib {
        swordmaster_female_1Tiles,
        swordmaster_female_1TilesLen,
        swordmaster_female_1Pal,
        swordmaster_female_1PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain
    };
    FMAW::TileAttributes tile_2_attrib {
        swordmaster_female_2Tiles,
        swordmaster_female_2TilesLen,
        swordmaster_female_2Pal,
        swordmaster_female_2PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain
    };
    FMAW::TileAttributes tile_3_attrib {
        swordmaster_female_3Tiles,
        swordmaster_female_3TilesLen,
        swordmaster_female_3Pal,
        swordmaster_female_3PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain
    };
    FMAW::TileAttributes tile_4_attrib {
        swordmaster_female_4Tiles,
        swordmaster_female_4TilesLen,
        swordmaster_female_4Pal,
        swordmaster_female_4PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain
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

    //--------------------------------------------------------------------------
    // Set up sprite.
    //--------------------------------------------------------------------------

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
    this->x = FMAW::FixedReal(128, 8);
    this->y = FMAW::FixedReal(64, 8);
}
