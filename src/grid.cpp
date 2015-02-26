// Copyright 2015 FMAW

#include <vector>

#include "./grid.h"

#include "./FMAW.h"

Grid::Grid() {
    this->rows = WINDOW_HEIGHT / CELL_HEIGHT;
    this->cols = WINDOW_WIDTH / CELL_WIDTH;
    this->cells = std::vector<Cell>(this->rows * this->cols);

    int tile_id = 0;
    int tiles_per_cell = CELL_WIDTH / TILE_WIDTH * CELL_HEIGHT / TILE_HEIGHT;

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            std::vector<FMAW::background_tile_id> tiles;
            for (int i = 0; i < tiles_per_cell; i++)
                tiles.push_back(tile_id++);
            IndexPath path {row, col};
            Cell c = this->cellAtIndexPath(path);
            c.tiles = tiles;
            c.background = FMAW::Background(0);
            if (row % 2 == col % 2) {
                c.setBackgroundType(CellBGBlack);
                this->cells.push_back(c);
            }
        }
    }
}

Cell Grid::cellAtIndexPath(IndexPath ip) {
    return this->cells[ ip.row * this->cols + ip.col ];
}

bool Grid::moveCharacterFromCellToCell(IndexPath from, IndexPath to,
                                       unsigned int duration) {
    Cell f = this->cellAtIndexPath(from);
    Cell t = this->cellAtIndexPath(to);
    if (!t.isOccupied() && f.isOccupied()) {
        FMAW::Character *c = f.getCharacter();
        c->animateToPosition(t.getCenter(), duration);
        t.setCharacter(c);
        f.setCharacter(nullptr);
        return true;
    }
    return false;
}

void Grid::render() {
    for (Cell cell : this->cells) {
        cell.render();
    }
}
