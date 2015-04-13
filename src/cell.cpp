// Copyright 2015 FMAW

#include "./cell.h"

#include <vector>

bool operator <(IndexPath const &left, IndexPath const &right) {
    return left.row < right.row || (left.row == right.row
                                    && left.col < right.col);
}

bool operator ==(IndexPath const &left, IndexPath const &right) {
    return left.row == right.row && left.col == right.col;
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
        newCharacter->decreaseAvailableActions();
        newCharacter->setPosition(this->center);
    }
    return prev;
}

int Cell::movementCost() {
    switch (this->backgroundType) {
        case CellBGBase:
            return COST_MOVE_CELL_BASE;
        case CellBGBridge:
        case CellBGBridgeH:
            return COST_MOVE_CELL_BRIDGE;
        case CellBGForest:
            return COST_MOVE_CELL_FOREST;
        case CellBGGrass:
            return COST_MOVE_CELL_GRASS;
        case CellBGMountain:
            return COST_MOVE_CELL_MOUNTAIN;
        case CellBGRiver:
        case CellBGRiverH:
            return COST_MOVE_CELL_RIVER;
        case CellBGCastle:
            return COST_MOVE_CELL_CASTLE;
        default:
            return COST_CELL_INFINITY;
    }
}

int Cell::sightCost() {
    switch (this->backgroundType) {
        case CellBGBase:
            return COST_SEE_CELL_BASE;
        case CellBGBridge:
        case CellBGBridgeH:
            return COST_SEE_CELL_BRIDGE;
        case CellBGForest:
            return COST_SEE_CELL_FOREST;
        case CellBGGrass:
            return COST_SEE_CELL_GRASS;
        case CellBGMountain:
            return COST_SEE_CELL_MOUNTAIN;
        case CellBGRiver:
        case CellBGRiverH:
            return COST_SEE_CELL_RIVER;
        case CellBGCastle:
            return COST_SEE_CELL_CASTLE;
        default:
            return COST_CELL_INFINITY;
    }
}

int Cell::terrainDefense() {
    switch (this->backgroundType) {
        case CellBGBase:
            return DEFENSE_CELL_BASE;
        case CellBGBridge:
        case CellBGBridgeH:
            return DEFENSE_CELL_BRIDGE;
        case CellBGForest:
            return DEFENSE_CELL_FOREST;
        case CellBGGrass:
            return DEFENSE_CELL_GRASS;
        case CellBGMountain:
            return DEFENSE_CELL_MOUNTAIN;
        case CellBGRiver:
        case CellBGRiverH:
            return DEFENSE_CELL_RIVER;
        default:
            return DEFAULT_DEFENSE;
    }
}

void Cell::renderBackground() {
    switch (this->backgroundType) {
        case CellBGBase:
        case CellBGBridge:
        case CellBGBridgeH:
        case CellBGForest:
        case CellBGGrass:
        case CellBGMountain:
        case CellBGRiver:
        case CellBGRiverH:
        case CellBGCastle:
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
        default:
            break;
    }
}

void Cell::renderFoggyBackground() {
    switch (this->backgroundType) {
        case CellBGBase:
        case CellBGBridge:
        case CellBGBridgeH:
        case CellBGForest:
        case CellBGGrass:
        case CellBGMountain:
        case CellBGRiver:
        case CellBGRiverH:
        case CellBGCastle:
            this->background.setScreenBaseBlock(2);
            for (int i = 0; i < this->tiles.size(); ++i) {
                this->background.setTile(
                    this->tiles[i],
                    FMAW::Tile(this->backgroundType +
                               NUM_BACKGROUNDS).imgMemory + i);
                this->background.setPalette(
                    this->tiles[i],
                    FMAW::Tile(this->backgroundType +
                               NUM_BACKGROUNDS).palMemory);
            }
            break;
        default:
            break;
    }
}

void Cell::renderCharacter() {
    if (this->characterInCell != nullptr) {
        this->characterInCell->render();
    }
}
