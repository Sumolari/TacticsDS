// Copyright 2015 FMAW

#include "./cell.h"

#include <vector>

#include "./gfx_brick.h"

Cell::Cell() {
    this->background = FMAW::Background(0);
}

void Cell::setCenter(FMAW::Point newCenter) {
    this->center = newCenter;
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
    if (newCharacter != nullptr) {
        newCharacter->setPosition(this->center);
    }
    return prev;
}

void Cell::renderBackground() {
    switch (this->backgroundType) {
        case CellBGBase:
        case CellBGBridge:
        case CellBGForest:
        case CellBGGrass:
        case CellBGMountain:
        case CellBGRiver:
            this->background.setScreenBaseBlock(2);
            for (int i = 0; i < this->tiles.size(); ++i) {
                this->background.setTile(
                    this->tiles[i],
                    FMAW::Tile(this->backgroundType).imgMemory + i);
                this->background.setPalette(
                    this->tiles[i],
                    FMAW::Tile(this->backgroundType).palMemory);
            }
            break;
        case CellBGBlack:
            for (auto tile_id : this->tiles) {
                this->background.setScreenBaseBlock(2);
                this->background.setTile(tile_id, FMAW::Tile(1));
            }
            break;
        case CellBGNone:
        case CellBGWhite:
        default:
            break;
    }
}

void Cell::renderCharacter() {
    if (this->characterInCell != nullptr) {
        this->characterInCell->render();
    }
}
