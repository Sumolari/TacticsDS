// Copyright 2015 FMAW

#include "./cursor.h"

#include "./gfx_cursor_square.h"
#include "./gfx_cursor_arrow.h"
#include "./gfx_cursor_cross.h"
#include "./gfx_cursor_sword.h"

Cursor::Cursor() :
    tileSquare(
        gfx_cursor_squareTiles,
        gfx_cursor_squareTilesLen,
        gfx_cursor_squarePal,
        gfx_cursor_squarePalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain),
    tileArrow(
        gfx_cursor_arrowTiles,
        gfx_cursor_arrowTilesLen,
        gfx_cursor_arrowPal,
        gfx_cursor_arrowPalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain),
    tileCross(
        gfx_cursor_crossTiles,
        gfx_cursor_crossTilesLen,
        gfx_cursor_crossPal,
        gfx_cursor_crossPalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain),
    tileSword(
        gfx_cursor_swordTiles,
        gfx_cursor_swordTilesLen,
        gfx_cursor_swordPal,
        gfx_cursor_swordPalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain),
    tile(FMAW::Tile(0)) {}

void Cursor::init() {
    this->tile = FMAW::Tile(this->tileSquare);

    this->sprite = FMAW::Sprite();

    this->setSquare();
    this->enable();
}

void Cursor::enable() {
    this->tile = FMAW::Tile(this->tileSquare, this->tile.ID);
    this->sprite.setSizeMode(FMAW::square16x16);
    this->sprite.enable();
}

void Cursor::disable() {
    this->sprite.clear();
}

void Cursor::setArrow() {
    this->tile = FMAW::Tile(this->tileArrow, this->tile.ID);
    this->sprite.setTile(this->tile);
}

void Cursor::setSquare() {
    this->tile = FMAW::Tile(this->tileSquare, this->tile.ID);
    this->sprite.setTile(this->tile);
}

void Cursor::setCross() {
    this->tile = FMAW::Tile(this->tileCross, this->tile.ID);
    this->sprite.setTile(this->tile);
}

void Cursor::setSword() {
    this->tile = FMAW::Tile(this->tileSword, this->tile.ID);
    this->sprite.setTile(this->tile);
}
