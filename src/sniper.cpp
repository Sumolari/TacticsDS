// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./sniper.h"

#include "./constants.h"

#include "./FMAW.h"

#include "./sniper_female_1_blue.h"
#include "./sniper_female_2_blue.h"
#include "./sniper_female_3_blue.h"
#include "./sniper_female_4_blue.h"

#include "./sniper_female_1_red.h"
#include "./sniper_female_2_red.h"
#include "./sniper_female_3_red.h"
#include "./sniper_female_4_red.h"

#define SPRITES_IDLE_ANIMATION 4

void Sniper::init() {
    this->reset();

    this->unitType = UNIT_TYPE_SNIPER;
    this->movementCapacity = 3;
    this->maximumAvailableActions = 1;
    this->currentAvailableActions = this->maximumAvailableActions;
    this->maximumHealth = 3;
    this->currentHealth = this->maximumHealth;
    this->minimumAttackRange = 2;
    this->maximumAttackRange = 3;
    this->attackPower = 10;
    this->print();

    int space_required = SPRITES_IDLE_ANIMATION * sizeof(
                             FMAW::TileAttributes *);
    this->tiles = reinterpret_cast<FMAW::TileAttributes **>(
                      malloc(space_required));

    FMAW::printf("This sniper has owner: %d", this->ownerID);

    //--------------------------------------------------------------------------
    // Decide proper tile based on current owner.
    //--------------------------------------------------------------------------

    auto sniper_female_1Tiles = (this->ownerID == 0) ?
                                     sniper_female_1_blueTiles :
                                     sniper_female_1_redTiles;
    auto sniper_female_1TilesLen = (this->ownerID == 0) ?
                                        sniper_female_1_blueTilesLen :
                                        sniper_female_1_redTilesLen;
    auto sniper_female_1Pal = (this->ownerID == 0) ?
                                   sniper_female_1_bluePal :
                                   sniper_female_1_redPal;
    auto sniper_female_1PalLen = (this->ownerID == 0) ?
                                      sniper_female_1_bluePalLen :
                                      sniper_female_1_redPalLen;

    auto sniper_female_2Tiles = (this->ownerID == 0) ?
                                     sniper_female_2_blueTiles :
                                     sniper_female_2_redTiles;
    auto sniper_female_2TilesLen = (this->ownerID == 0) ?
                                        sniper_female_2_blueTilesLen :
                                        sniper_female_2_redTilesLen;
    auto sniper_female_2Pal = (this->ownerID == 0) ?
                                   sniper_female_2_bluePal :
                                   sniper_female_2_redPal;
    auto sniper_female_2PalLen = (this->ownerID == 0) ?
                                      sniper_female_2_bluePalLen :
                                      sniper_female_2_redPalLen;

    auto sniper_female_3Tiles = (this->ownerID == 0) ?
                                     sniper_female_3_blueTiles :
                                     sniper_female_3_redTiles;
    auto sniper_female_3TilesLen = (this->ownerID == 0) ?
                                        sniper_female_3_blueTilesLen :
                                        sniper_female_3_redTilesLen;
    auto sniper_female_3Pal = (this->ownerID == 0) ?
                                   sniper_female_3_bluePal :
                                   sniper_female_3_redPal;
    auto sniper_female_3PalLen = (this->ownerID == 0) ?
                                      sniper_female_3_bluePalLen :
                                      sniper_female_3_redPalLen;

    auto sniper_female_4Tiles = (this->ownerID == 0) ?
                                     sniper_female_4_blueTiles :
                                     sniper_female_4_redTiles;
    auto sniper_female_4TilesLen = (this->ownerID == 0) ?
                                        sniper_female_4_blueTilesLen :
                                        sniper_female_4_redTilesLen;
    auto sniper_female_4Pal = (this->ownerID == 0) ?
                                   sniper_female_4_bluePal :
                                   sniper_female_4_redPal;
    auto sniper_female_4PalLen = (this->ownerID == 0) ?
                                      sniper_female_4_bluePalLen :
                                      sniper_female_4_redPalLen;

    //--------------------------------------------------------------------------
    // Load tile.
    //--------------------------------------------------------------------------

    this->tiles[0] = new FMAW::t_tile_attrib(
        sniper_female_1Tiles,
        sniper_female_1TilesLen,
        sniper_female_1Pal,
        sniper_female_1PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[1] = new FMAW::t_tile_attrib(
        sniper_female_2Tiles,
        sniper_female_2TilesLen,
        sniper_female_2Pal,
        sniper_female_2PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[2] = new FMAW::t_tile_attrib(
        sniper_female_3Tiles,
        sniper_female_3TilesLen,
        sniper_female_3Pal,
        sniper_female_3PalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain);
    this->tiles[3] = new FMAW::t_tile_attrib(
        sniper_female_4Tiles,
        sniper_female_4TilesLen,
        sniper_female_4Pal,
        sniper_female_4PalLen,
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

    this->width = SNIPER_HEIGHT;
    this->height = SNIPER_HEIGHT;
    this->sprite.setSizeMode(FMAW::square16x16);
    this->sprite.setTile(*(this->tiles[this->currentTileID]));
    this->sprite.enable();
}

void Sniper::update() {
    if (this->hasAvailableActions()) {
        this->currentTileID += 1;
        this->currentTileID %= SPRITES_IDLE_ANIMATION;

        this->tile = new FMAW::Tile(*(this->tiles[this->currentTileID]),
                                    this->tile->ID);

        this->sprite.setTile(*(this->tile));
    }
}

void Sniper::update_freq(){
	FMAW::Timer::dequeue_function(this->updateID);
	
	auto _update = [this](int ID) {
        this->update();
    };
    
    //TODO decent time calculation
    int t = 200*(this->maximumHealth / this->currentHealth);
    
	this->updateID = FMAW::Timer::enqueue_function(_update, t, true);
}

void Sniper::reset() {
    this->x = FMAW::FixedReal(128, 8);
    this->y = FMAW::FixedReal(64, 8);
}

void Sniper::print() {
    FMAW::printf("%d of %d actions available, with %d movements",
                 this->currentAvailableActions, this->maximumAvailableActions,
                 this->movementCapacity);
}

Sniper::~Sniper() {
    FMAW::Timer::dequeue_function(this->updateID);
    for (int i = 0; i < SPRITES_IDLE_ANIMATION; i++)  {
        delete this->tiles[i];
    }
    free(this->tiles);
    delete this->tile;
}
