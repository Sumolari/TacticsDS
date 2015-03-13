// Copyright 2015 FMAW

#include <vector>

#include "./turnManager.h"
#include "./grid.h"

#include "./FMAW.h"

#define CURSOR_WIDTH  32
#define CURSOR_HEIGHT 32

Grid::Grid():
    downArrowCallbackID(-1),
    upArrowCallbackID(-1),
    leftArrowCallbackID(-1),
    rightArrowCallbackID(-1),
    aButtonCallbackID(-1) {
    this->pickedUpCell = { -1, -1 };
    this->rows = WINDOW_HEIGHT / CELL_HEIGHT;
    this->cols = WINDOW_WIDTH / CELL_WIDTH;
    this->cells = std::vector<Cell>(this->rows * this->cols);

    int cols_per_cell = CELL_WIDTH / TILE_WIDTH;
    int rows_per_cell = CELL_HEIGHT / TILE_HEIGHT;

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            FMAW::Point center = {col * 16 + 16, row * 16 + 16};

            std::vector<FMAW::background_tile_id> tiles;

            int upperLeft = col * cols_per_cell + row * this->cols *
                            cols_per_cell * rows_per_cell;

            for (int j = 0; j < rows_per_cell; j++)
                for (int i = 0; i < cols_per_cell; i++) {
                    tiles.push_back(upperLeft + j * this->cols
                                    * cols_per_cell + i);
                }
            IndexPath path {row, col};
            Cell *c = this->cellAtIndexPath(path);
            c->tiles = tiles;
            c->setCenter(center);
            c->background = FMAW::Background(0);
            if (row % 2 == col % 2) {
                c->setBackgroundType(CellBGGrass);
            } else {
                c->setBackgroundType(CellBGBase);
            }
        }
    }

    this->pickedUpCell = {0, 0};
}

void Grid::initCursor() {
    this->cursor.init();
    this->setSquareCursor();
}

Cell *Grid::cellAtIndexPath(IndexPath ip) {
    return &this->cells[ ip.row * this->cols + ip.col ];
}

Cell *Grid::cellAtSelectedPath() {
    return this->cellAtIndexPath(this->selectedPath);
}

IndexPath Grid::getSelectedPath() {
    return this->selectedPath;
}

bool Grid::moveCharacterFromCellToCell(IndexPath from, IndexPath to,
                                       unsigned int duration) {
    Cell *f = this->cellAtIndexPath(from);
    Cell *t = this->cellAtIndexPath(to);
    if (!t->isOccupied() && f->isOccupied()) {
        Unit *c = f->getCharacter();
        t->setCharacter(c);
        c->setPosition(f->getCenter());
        c->animateToPosition(t->getCenter(), duration);
        f->setCharacter(nullptr);
        return true;
    }
    return false;
}

void Grid::renderBackground() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath p{row, col};
            this->cellAtIndexPath(p)->renderBackground();
        }
    }
}

void Grid::renderCharacters() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath p{row, col};
            this->cellAtIndexPath(p)->renderCharacter();
        }
    }
    this->cursor.render();
}

int Grid::numRows() {
    return this->rows;
}

int Grid::numCols() {
    return this->cols;
}

//------------------------------------------------------------------------------
// Cell selection.
//------------------------------------------------------------------------------

bool Grid::selectCellAtIndexPath(IndexPath path) {
    FMAW::printf("Quieres seleccionar la celda %d %d", path.row, path.col);
    if (path.row < this->rows && path.col < this->cols && path.row >= 0 &&
            path.col >= 0 && (path.row != this->selectedPath.row ||
                              path.col != this->selectedPath.col)) {
        this->selectedPath = path;
        FMAW::printf("Seleccionada celda %d %d", path.row, path.col);

        FMAW::Point p = this->cellAtSelectedPath()->getCenter();

        this->cursor.setPosition({p.x - 16, p.y - 16});
        return true;
    }
    return false;
}

bool Grid::selectBottomCell() {
    return this->selectCellAtIndexPath({this->selectedPath.row + 1,
                                        this->selectedPath.col
                                       });
}

bool Grid::selectTopCell() {
    return this->selectCellAtIndexPath({this->selectedPath.row - 1,
                                        this->selectedPath.col
                                       });
}

bool Grid::selectLeftCell() {
    return this->selectCellAtIndexPath({this->selectedPath.row,
                                        this->selectedPath.col - 1
                                       });
}

bool Grid::selectRightCell() {
    return this->selectCellAtIndexPath({this->selectedPath.row,
                                        this->selectedPath.col + 1
                                       });
}

//------------------------------------------------------------------------------
// Cursor settings.
//------------------------------------------------------------------------------

void Grid::setSquareCursor() {
    this->cursor.setSquare();
}

void Grid::setArrowCursor() {
    this->cursor.setArrow();
}

void Grid::setCrossCursor() {
    this->cursor.setCross();
}

//------------------------------------------------------------------------------
// Callbacks.
//------------------------------------------------------------------------------

void Grid::enqueueCallbacks() {
    auto releaseLeftArrow = [this]() {
        this->selectLeftCell();
    };
    if (this->leftArrowCallbackID == -1) {
        this->leftArrowCallbackID = FMAW::Input::onButtonArrowLeftReleased(
                                        releaseLeftArrow);
    }

    auto releaseRightArrow = [this]() {
        this->selectRightCell();
    };
    if (this->rightArrowCallbackID == -1) {
        this->rightArrowCallbackID = FMAW::Input::onButtonArrowRightReleased(
                                         releaseRightArrow);
    }

    auto releaseUpArrow = [this]() {
        this->selectTopCell();
    };
    if (this->upArrowCallbackID == -1) {
        this->upArrowCallbackID = FMAW::Input::onButtonArrowUpReleased(
                                      releaseUpArrow);
    }

    auto releaseDownArrow = [this]() {
        this->selectBottomCell();
    };
    if (this->downArrowCallbackID == -1) {
        this->downArrowCallbackID = FMAW::Input::onButtonArrowDownReleased(
                                        releaseDownArrow);
    }

    auto releaseA = [this]() {
        if (this->cellAtSelectedPath()->isOccupied() &&
                this->cellAtSelectedPath()->getCharacter()->getOwner() ==
                TurnManager::currentPlayerID()) {
            this->pickedUpCell.row = this->getSelectedPath().row;
            this->pickedUpCell.col = this->getSelectedPath().col;
            this->setArrowCursor();
            FMAW::printf("Se ha marcado la celda %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col);
        } else if (this->cellAtSelectedPath()->isOccupied() &&
                   this->cellAtSelectedPath()->getCharacter()->getOwner() !=
                   TurnManager::currentPlayerID()) {
            this->pickedUpCell.row = -1;
            this->pickedUpCell.col = -1;
            this->setSquareCursor();
            FMAW::printf("Hay un enemigo en la celda %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col);
        } else if (this->pickedUpCell.row >= 0 && this->pickedUpCell.col >= 0) {
            FMAW::printf("Se mueve de %d %d a %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col,
                         this->getSelectedPath().row,
                         this->getSelectedPath().col);
            this->moveCharacterFromCellToCell(this->pickedUpCell,
                                              this->getSelectedPath(), 500);
            this->setSquareCursor();
        }
    };
    if (this->aButtonCallbackID == -1) {
        this->aButtonCallbackID = FMAW::Input::onButtonAReleased(releaseA);
    }
}

void Grid::dequeueCallbacks() {
    if (this->upArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->upArrowCallbackID);
    }
    if (this->rightArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->rightArrowCallbackID);
    }
    if (this->leftArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->leftArrowCallbackID);
    }
    if (this->downArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->downArrowCallbackID);
    }
    if (this->aButtonCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->aButtonCallbackID);
    }
}
