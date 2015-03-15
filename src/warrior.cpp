// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./warrior.h"

#include "./constants.h"

#include "./FMAW.h"

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

    this->unitType = UNIT_TYPE_WARRIOR;
    this->movementCapacity = 4;
    this->maximumAvailableActions = 1;
    this->currentAvailableActions = 1;
    this->print();

    int space_required = SPRITES_IDLE_ANIMATION * sizeof(
                             FMAW::TileAttributes *);
    this->tiles = reinterpret_cast<FMAW::TileAttributes **>(
                      malloc(space_required));

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

    this->tiles[0] = new FMAW::t_tile_attrib(
        swordmaster_female_1Tiles,
        swordmaster_female_1TilesLen,
        swordmaster_female_1Pal,
        swordmaster_female_1PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[1] = new FMAW::t_tile_attrib(
        swordmaster_female_2Tiles,
        swordmaster_female_2TilesLen,
        swordmaster_female_2Pal,
        swordmaster_female_2PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[2] = new FMAW::t_tile_attrib(
        swordmaster_female_3Tiles,
        swordmaster_female_3TilesLen,
        swordmaster_female_3Pal,
        swordmaster_female_3PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[3] = new FMAW::t_tile_attrib(
        swordmaster_female_4Tiles,
        swordmaster_female_4TilesLen,
        swordmaster_female_4Pal,
        swordmaster_female_4PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);

    this->currentTileID = 0;

    this->tile = new FMAW::Tile(*(this->tiles[this->currentTileID]));

    //--------------------------------------------------------------------------
    // Set up sprite.
    //--------------------------------------------------------------------------

    auto _update = [this](int ID) {
        this->update();
    };
    this->updateID = FMAW::Timer::enqueue_function(_update, 200, true);

    this->width = WARRIOR_HEIGHT;
    this->height = WARRIOR_HEIGHT;
    this->sprite.setSizeMode(FMAW::square16x16);
    this->sprite.setTile(*(this->tiles[this->currentTileID]));
    this->sprite.enable();
}

void Warrior::update() {
    if (this->hasAvailableActions()) {
        this->currentTileID += 1;
        this->currentTileID %= SPRITES_IDLE_ANIMATION;

        this->tile = new FMAW::Tile(*(this->tiles[this->currentTileID]),
                                    this->tile->ID);

        this->sprite.setTile(*(this->tile));
    }
}

void Warrior::reset() {
    this->x = FMAW::FixedReal(128, 8);
    this->y = FMAW::FixedReal(64, 8);
}

void Warrior::print() {
    FMAW::printf("%d of %d actions available, with %d movements",
                 this->currentAvailableActions, this->maximumAvailableActions,
                 this->movementCapacity);
}

Warrior::~Warrior() {
    FMAW::Timer::dequeue_function(this->updateID);
    for (int i = 0; i < SPRITES_IDLE_ANIMATION; i++)  {
        delete this->tiles[i];
    }
    free(this->tiles);
    delete this->tile;
}
