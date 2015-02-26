// Copyright 2015 FMAW

#include "./cell.h"

#include <vector>

#include "./black.h"

#include "./gfx_brick.h"

Cell::Cell() {
    this->background = FMAW::Background(0);
}

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

void Cell::renderBackground() {
    switch (this->backgroundType) {
        case CellBGBlack:
            FMAW::printf("NEGRA");
            for (auto tile_id : this->tiles) {
                this->background.setScreenBaseBlock(2);
                this->background.setTile(tile_id, FMAW::Tile(1));
            }
            break;
        case CellBGNone:
        case CellBGWhite:
        default:
            FMAW::printf("ESTA NO SE PINTA");
            break;
    }
    /*
    if (this->characterInCell != nullptr) {
        this->characterInCell->render();
    }
    */
}
