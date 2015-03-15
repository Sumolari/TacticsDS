// Copyright 2015 FMAW

#include <vector>
#include <queue>
#include <map>
#include <string>

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
    aButtonCallbackID(-1),
    savefile(nullptr) {
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

    this->pickedUpCell = { -1, -1};
    this->recomputeReachableCells();
}

bool Grid::enableSavingHistory(std::string filename) {
    this->savefile = FMAW::IO::fopen(("./" + filename).c_str(), "w+");

    if (this->savefile == NULL) {
        this->savefile = nullptr;
        return false;
    }

    FMAW::IO::fprintf(this->savefile, "%d %d\n", this->rows, this->cols);

    // Print terrain information.

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath path {row, col};
            Cell *c = this->cellAtIndexPath(path);

            FMAW::IO::fprintf(this->savefile, "%d", c->getBackgroundType());

            if (col < this->cols - 1)
                FMAW::IO::fprintf(this->savefile, " ");
        }
        FMAW::IO::fprintf(this->savefile, "\n");
    }

    // Print unit type information.

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath path {row, col};
            Cell *c = this->cellAtIndexPath(path);
            Unit *u = c->getCharacter();

            if (c->isOccupied()) {
                FMAW::IO::fprintf(this->savefile, "%d", u->getUnitType());
            } else {
                FMAW::IO::fprintf(this->savefile, "%d", UNIT_TYPE_EMPTY);
            }

            if (col < this->cols - 1) FMAW::IO::fprintf(this->savefile, " ");
        }
        FMAW::IO::fprintf(this->savefile, "\n");
    }

    // Print unit owner information.

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath path {row, col};
            Cell *c = this->cellAtIndexPath(path);
            Unit *u = c->getCharacter();

            if (c->isOccupied()) {
                FMAW::IO::fprintf(this->savefile, "%d", u->getOwner());
            } else {
                FMAW::IO::fprintf(this->savefile, "%d", UNIT_OWNER_NONE);
            }

            if (col < this->cols - 1) FMAW::IO::fprintf(this->savefile, " ");
        }
        FMAW::IO::fprintf(this->savefile, "\n");
    }

    FMAW::IO::fflush(this->savefile);

    return true;
}

void Grid::resetUnitMovements() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath p{row, col};
            Cell *c = this->cellAtIndexPath(p);
            if (c->isOccupied()) {
                c->getCharacter()->resetAvailableActions();
            }
        }
    }
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
        if (this->savefile != nullptr) {
            FMAW::IO::fprintf(this->savefile, "%d %d %d %d\n",
                              from.row, from.col, to.row, to.col);
            FMAW::IO::fflush(this->savefile);
        }

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

bool Grid::hasPickedUpCell() {
    return (this->pickedUpCell.row != -1 && this->pickedUpCell.col != -1);
}

bool Grid::selectCellAtIndexPath(IndexPath path) {
    if (path.row < this->rows && path.col < this->cols && path.row >= 0 &&
            path.col >= 0 && (path.row != this->selectedPath.row ||
                              path.col != this->selectedPath.col)) {
        this->selectedPath = path;
        FMAW::Point p = this->cellAtSelectedPath()->getCenter();
        this->cursor.setPosition({p.x - 16, p.y - 16});

        if (this->hasPickedUpCell()) {
            if (this->reachableCells[this->selectedPath]) {
                this->setArrowCursor();
            } else {
                this->setCrossCursor();
            }
        } else {
            Cell *c = this->cellAtSelectedPath();
            if (c->isOccupied() && !c->getCharacter()->hasAvailableActions()) {
                this->setCrossCursor();
            } else {
                this->setSquareCursor();
            }
        }

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

void Grid::resetPickedUpCell() {
    this->pickedUpCell.row = -1;
    this->pickedUpCell.col = -1;
    this->setSquareCursor();
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
        Cell *c = this->cellAtSelectedPath();
        Unit *u = c->getCharacter();
        if (c->isOccupied() && u->hasAvailableActions() &&
                u->getOwner() == TurnManager::currentPlayerID()) {
            // If cell is occupied by a character owned by current player and
            // it has available actions then we pick up it.
            this->pickedUpCell.row = this->getSelectedPath().row;
            this->pickedUpCell.col = this->getSelectedPath().col;
            this->setArrowCursor();
            FMAW::printf("Se ha marcado la celda %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col);
            this->recomputeReachableCells();
        } else if (c->isOccupied() && u->getOwner() !=
                   TurnManager::currentPlayerID()) {
            // If cell is occupied by a character owned by an enemy we release
            // previously picked up cell and we reset the cursor.
            this->resetPickedUpCell();
            this->setSquareCursor();
            FMAW::printf("Hay un enemigo en la celda %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col);
        } else if (this->hasPickedUpCell() &&
                   this->reachableCells[this->getSelectedPath()]) {
            // If there is a picked up cell and we can move to selected cell
            // then we move the character and reset picked up cell.
            FMAW::printf("Se mueve de %d %d a %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col,
                         this->getSelectedPath().row,
                         this->getSelectedPath().col);
            this->moveCharacterFromCellToCell(this->pickedUpCell,
                                              this->getSelectedPath(), 100);
            u->decreaseAvailableActions();
            this->resetPickedUpCell();
            if (!u->hasAvailableActions()) {
                this->setCrossCursor();
            }
        }
    };
    if (this->aButtonCallbackID == -1) {
        this->aButtonCallbackID = FMAW::Input::onButtonAReleased(releaseA);
    }
}

void Grid::dequeueCallbacks() {
    if (this->upArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->upArrowCallbackID);
        this->upArrowCallbackID = -1;
    }
    if (this->rightArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->rightArrowCallbackID);
        this->rightArrowCallbackID = -1;
    }
    if (this->leftArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->leftArrowCallbackID);
        this->leftArrowCallbackID = -1;
    }
    if (this->downArrowCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->downArrowCallbackID);
        this->downArrowCallbackID = -1;
    }
    if (this->aButtonCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->aButtonCallbackID);
        this->aButtonCallbackID = -1;
    }
}

//------------------------------------------------------------------------------
// Rechable cells helpers.
//------------------------------------------------------------------------------

void Grid::recomputeReachableCells() {
    this->reachableCells.clear();

    if (this->pickedUpCell.row == -1 || this->pickedUpCell.col == -1) {
        for (int row = 0; row < this->rows; row++) {
            for (int col = 0; col < this->cols; col++) {
                this->reachableCells[ {row, col}] = true;
            }
        }
    } else {
        std::map<IndexPath, int> reachCost;

        Cell *cell = this->cellAtIndexPath(this->pickedUpCell);
        Unit *unit = cell->getCharacter();
        int maxMove = unit->getMovementCapacity();

        // First no cell is reachable.
        for (int row = 0; row < this->rows; row++) {
            for (int col = 0; col < this->cols; col++) {
                reachCost[ {row, col}] = COST_CELL_INFINITY;
                this->reachableCells[ {row, col}] = false;
            }
        }

        // Only cell reachable is the first one.
        reachCost[ this->pickedUpCell] = 0;
        this->reachableCells[ this->pickedUpCell ] = true;

        // When the cost of a cell changes we explore its neighbours.
        std::queue<IndexPath> pathsToCheck({ this->pickedUpCell });

        // While we have some cell to check we check it...
        while (pathsToCheck.size() > 0) {
            IndexPath path = pathsToCheck.front();  // Cell to check.
            pathsToCheck.pop();  // We remove it as we have checked it.
            // If we go up...
            if (path.row > 0) {
                IndexPath u = { path.row - 1, path.col };
                int c = this->cellAtIndexPath(u)->movementCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[u] && newCost <= maxMove) {
                    reachCost[u] = newCost;
                    this->reachableCells[u] = true;
                    pathsToCheck.push(u);
                }
            }
            // If we go down...
            if (path.row < this->rows - 1) {
                IndexPath d = { path.row + 1, path.col };
                int c = this->cellAtIndexPath(d)->movementCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[d] && newCost <= maxMove) {
                    reachCost[d] = newCost;
                    this->reachableCells[d] = true;
                    pathsToCheck.push(d);
                }
            }
            // If we go left...
            if (path.col > 0) {
                IndexPath l = { path.row, path.col - 1 };
                int c = this->cellAtIndexPath(l)->movementCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[l] && newCost <= maxMove) {
                    reachCost[l] = newCost;
                    this->reachableCells[l] = true;
                    pathsToCheck.push(l);
                }
            }
            // If we go right...
            if (path.col < this->cols - 1) {
                IndexPath r = { path.row, path.col + 1 };
                int c = this->cellAtIndexPath(r)->movementCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[r] && newCost <= maxMove) {
                    reachCost[r] = newCost;
                    this->reachableCells[r] = true;
                    pathsToCheck.push(r);
                }
            }
        }
    }
}
