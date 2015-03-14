// Copyright 2015 FMAW

#include "./cell.h"

#include <vector>

#include "./gfx_brick.h"

bool operator <(IndexPath const &left, IndexPath const &right) {
    return left.row < right.row || (left.row == right.row
                                    && left.col < right.col);
}

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

Unit *Cell::getCharacter() {
    return this->characterInCell;
}

Unit *Cell::setCharacter(Unit *newCharacter) {
    Unit *prev = this->characterInCell;
    this->characterInCell = newCharacter;
    if (newCharacter != nullptr) {
        newCharacter->setPosition(this->center);
    }
    return prev;
}

int Cell::movementCost() {
    switch (this->backgroundType) {
        case CellBGBase:
            return COST_CELL_BASE;
        case CellBGBridge:
            return COST_CELL_BRIDGE;
        case CellBGForest:
            return COST_CELL_FOREST;
        case CellBGGrass:
            return COST_CELL_GRASS;
        case CellBGMountain:
            return COST_CELL_MOUNTAIN;
        case CellBGRiver:
            return COST_CELL_RIVER;
        case CellBGBlack:
        case CellBGNone:
        case CellBGWhite:
        default:
            return COST_CELL_INFINITY;
    }
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
