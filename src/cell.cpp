// Copyright 2015 FMAW

#include "./cell.h"

#include <vector>

#include "./black.h"

#include "./gfx_brick.h"


/**
 * Black tile.
 */
FMAW::TileAttributes black_tile_attributes {
    blackTiles,
    blackTilesLen,
    blackPal,
    blackPalLen,
    FMAW::TypeBackground
};
FMAW::Tile black_tile(black_tile_attributes);

CellBackgroundType Cell::getBackgroundType() {
    return this->backgroundType;
}

void Cell::setBackgroundType(CellBackgroundType type) {
    this->backgroundType = type;
}

FMAW::Point Cell::getCenter() {
    return this->center;
}

bool Cell::isOccupied() {
    return this->characterInCell != nullptr;
}

FMAW::Character *Cell::getCharacter() {
    return this->characterInCell;
}

FMAW::Character *Cell::setCharacter(FMAW::Character *newCharacter) {
    FMAW::Character *prev = this->characterInCell;
    this->characterInCell = newCharacter;
    return prev;
}

void Cell::render() {
    switch (this->backgroundType) {
        case CellBGBlack:
            for (auto tile_id : this->tiles) {
                this->background.setTile(tile_id, black_tile);
            }
            break;
        case CellBGNone:
        case CellBGWhite:
        default:
            break;
    }
    if (this->characterInCell != nullptr) {
        this->characterInCell->render();
    }
}
