// Copyright 2015 FMAW

#include "./cursor.h"

#include "./gfx_cursor_square.h"
#include "./gfx_cursor_arrow.h"
#include "./gfx_cursor_cross.h"

Cursor::Cursor() :
    tileSquare(FMAW::Tile(0)),
    tileArrow(FMAW::Tile(0)),
    tileCross(FMAW::Tile(0)) {}

void Cursor::init() {
    FMAW::TileAttributes cursor_square_attributes {
        gfx_cursor_squareTiles,
        gfx_cursor_squareTilesLen,
        gfx_cursor_squarePal,
        gfx_cursor_squarePalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain
    };
    this->tileSquare = FMAW::Tile(cursor_square_attributes);

    FMAW::TileAttributes cursor_arrow_attributes {
        gfx_cursor_arrowTiles,
        gfx_cursor_arrowTilesLen,
        gfx_cursor_arrowPal,
        gfx_cursor_arrowPalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain
    };
    this->tileArrow = FMAW::Tile(cursor_arrow_attributes);

    FMAW::TileAttributes cursor_cross_attributes {
        gfx_cursor_crossTiles,
        gfx_cursor_crossTilesLen,
        gfx_cursor_crossPal,
        gfx_cursor_crossPalLen,
        FMAW::TypeSprite,
        FMAW::ScreenMain
    };
    this->tileCross = FMAW::Tile(cursor_cross_attributes);

    this->sprite.setSizeMode(FMAW::square16x16);
    this->sprite.enable();

    this->setSquare();
}

void Cursor::setArrow() {
    this->sprite.setTile(this->tileArrow);
}

void Cursor::setSquare() {
    this->sprite.setTile(this->tileSquare);
}

void Cursor::setCross() {
    this->sprite.setTile(this->tileCross);
}
