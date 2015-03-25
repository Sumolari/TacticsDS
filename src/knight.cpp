// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./knight.h"

#include "./constants.h"

#include "./FMAW.h"

#include "./free_knight_1_blue.h"
#include "./free_knight_2_blue.h"
#include "./free_knight_3_blue.h"
#include "./free_knight_4_blue.h"

#include "./free_knight_1_red.h"
#include "./free_knight_2_red.h"
#include "./free_knight_3_red.h"
#include "./free_knight_4_red.h"

#define SPRITES_IDLE_ANIMATION 4

void Knight::init() {
    this->reset();

    this->unitType = UNIT_TYPE_KNIGHT;
    this->movementCapacity = 6;
    this->sightDistance = 8;
    this->maximumAvailableActions = 2;
    this->currentAvailableActions = this->maximumAvailableActions;
    this->maximumHealth = 2;
    this->currentHealth = this->maximumHealth;
    this->minimumAttackRange = 1;
    this->maximumAttackRange = 1;
    this->attackPower = 5;
    this->print();

    int space_required = SPRITES_IDLE_ANIMATION * sizeof(
                             FMAW::TileAttributes *);
    this->tiles = reinterpret_cast<FMAW::TileAttributes **>(
                      malloc(space_required));

    FMAW::printf("This knight has owner: %d", this->ownerID);

    //--------------------------------------------------------------------------
    // Decide proper tile based on current owner.
    //--------------------------------------------------------------------------

    auto free_knight_1Tiles = (this->ownerID == 0) ?
                              free_knight_1_blueTiles :
                              free_knight_1_redTiles;
    auto free_knight_1TilesLen = (this->ownerID == 0) ?
                                 free_knight_1_blueTilesLen :
                                 free_knight_1_redTilesLen;
    auto free_knight_1Pal = (this->ownerID == 0) ?
                            free_knight_1_bluePal :
                            free_knight_1_redPal;
    auto free_knight_1PalLen = (this->ownerID == 0) ?
                               free_knight_1_bluePalLen :
                               free_knight_1_redPalLen;

    auto free_knight_2Tiles = (this->ownerID == 0) ?
                              free_knight_2_blueTiles :
                              free_knight_2_redTiles;
    auto free_knight_2TilesLen = (this->ownerID == 0) ?
                                 free_knight_2_blueTilesLen :
                                 free_knight_2_redTilesLen;
    auto free_knight_2Pal = (this->ownerID == 0) ?
                            free_knight_2_bluePal :
                            free_knight_2_redPal;
    auto free_knight_2PalLen = (this->ownerID == 0) ?
                               free_knight_2_bluePalLen :
                               free_knight_2_redPalLen;

    auto free_knight_3Tiles = (this->ownerID == 0) ?
                              free_knight_3_blueTiles :
                              free_knight_3_redTiles;
    auto free_knight_3TilesLen = (this->ownerID == 0) ?
                                 free_knight_3_blueTilesLen :
                                 free_knight_3_redTilesLen;
    auto free_knight_3Pal = (this->ownerID == 0) ?
                            free_knight_3_bluePal :
                            free_knight_3_redPal;
    auto free_knight_3PalLen = (this->ownerID == 0) ?
                               free_knight_3_bluePalLen :
                               free_knight_3_redPalLen;

    auto free_knight_4Tiles = (this->ownerID == 0) ?
                              free_knight_4_blueTiles :
                              free_knight_4_redTiles;
    auto free_knight_4TilesLen = (this->ownerID == 0) ?
                                 free_knight_4_blueTilesLen :
                                 free_knight_4_redTilesLen;
    auto free_knight_4Pal = (this->ownerID == 0) ?
                            free_knight_4_bluePal :
                            free_knight_4_redPal;
    auto free_knight_4PalLen = (this->ownerID == 0) ?
                               free_knight_4_bluePalLen :
                               free_knight_4_redPalLen;

    //--------------------------------------------------------------------------
    // Load tile.
    //--------------------------------------------------------------------------

    this->tiles[0] = new FMAW::t_tile_attrib(
        free_knight_1Tiles,
        free_knight_1TilesLen,
        free_knight_1Pal,
        free_knight_1PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[1] = new FMAW::t_tile_attrib(
        free_knight_2Tiles,
        free_knight_2TilesLen,
        free_knight_2Pal,
        free_knight_2PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[2] = new FMAW::t_tile_attrib(
        free_knight_3Tiles,
        free_knight_3TilesLen,
        free_knight_3Pal,
        free_knight_3PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[3] = new FMAW::t_tile_attrib(
        free_knight_4Tiles,
        free_knight_4TilesLen,
        free_knight_4Pal,
        free_knight_4PalLen,
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

    this->width = KNIGHT_HEIGHT;
    this->height = KNIGHT_HEIGHT;
    this->sprite.setSizeMode(FMAW::square16x16);
    this->sprite.setTile(*(this->tiles[this->currentTileID]));
    this->sprite.enable();
}

void Knight::update() {
    if (this->hasAvailableActions()) {
        this->currentTileID += 1;
        this->currentTileID %= SPRITES_IDLE_ANIMATION;

        int id = this->tile->ID;
        delete this->tile;

        this->tile = new FMAW::Tile(*(this->tiles[this->currentTileID]), id);

        this->sprite.setTile(*(this->tile));
    }
}

void Knight::update_freq() {
    FMAW::Timer::dequeue_function(this->updateID);

    auto _update = [this](int ID) {
        this->update();
    };

    // TODO(victor) decent time calculation
    int t = 200 * (this->maximumHealth / this->currentHealth);

    this->updateID = FMAW::Timer::enqueue_function(_update, t, true);
}

void Knight::reset() {
    this->x = FMAW::FixedReal(128, 8);
    this->y = FMAW::FixedReal(64, 8);
}

void Knight::print() {
    FMAW::printf("%d of %d actions available, with %d movements",
                 this->currentAvailableActions, this->maximumAvailableActions,
                 this->movementCapacity);
}

Knight::~Knight() {
    FMAW::Timer::dequeue_function(this->updateID);
    for (int i = 0; i < SPRITES_IDLE_ANIMATION; i++)  {
        delete this->tiles[i];
    }
    free(this->tiles);
    delete this->tile;
}
