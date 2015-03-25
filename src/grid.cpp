// Copyright 2015 FMAW

#include <vector>
#include <queue>
#include <map>
#include <string>

#include "./turnManager.h"
#include "./grid.h"
#include "./constants.h"

#include "./FMAW.h"

#define CURSOR_WIDTH  32
#define CURSOR_HEIGHT 32

Grid::Grid():
    downArrowCallbackID(-1),
    upArrowCallbackID(-1),
    leftArrowCallbackID(-1),
    rightArrowCallbackID(-1),
    aButtonCallbackID(-1),
    bButtonCallbackID(-1),
    savefile(nullptr),
    playingSavedFile(false) {
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
    this->recomputeAttackableCells();

    this->selectSoundID = FMAW::Sound::registerFX(
                              FMAW::Sound::effectWithSoundID(SFX_SELECT));
    this->forbiddenSoundID = FMAW::Sound::registerFX(
                                 FMAW::Sound::effectWithSoundID(SFX_FORBIDDEN));
    this->hitSoundID = FMAW::Sound::registerFX(
                           FMAW::Sound::effectWithSoundID(SFX_HIT));
}

bool Grid::enableSavingHistory(std::string filename) {
    if (this->savefile != nullptr) {
        FMAW::IO::fclose(this->savefile);
        this->savefile = nullptr;
    }

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

void Grid::playSavedHistory(std::string filename,
                            std::function<void(bool)> callback) {
    this->dequeueCallbacks();

    if (this->savefile != nullptr) {
        FMAW::IO::fclose(this->savefile);
        this->savefile = nullptr;
    }
    this->savefile = FMAW::IO::fopen(("./" + filename).c_str(), "r");

    if (this->savefile == NULL) {
        this->savefile = nullptr;
        this->playingSavedFile = false;
        callback(false);
        return;
    }

    this->clearGridUnits();
    this->playingSavedFile = true;
    this->cursor.disable();
    FMAW::Tile::releaseAllSpriteMemory();

    int rows, cols, aux;

    FMAW::IO::fscanf(this->savefile, "%d %d\n", &rows, &cols);

    // Load terrain information.
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (col < cols - 1) {
                FMAW::IO::fscanf(this->savefile, "%d ", &aux);
            } else {
                FMAW::IO::fscanf(this->savefile, "%d\n", &aux);
            }

            IndexPath path {row, col};
            Cell *c = this->cellAtIndexPath(path);
            c->setBackgroundType(
                static_cast<CellBackgroundType>(aux));

            c->renderBackground();
        }
    }

    FMAW::printf("Terrain loaded");

    std::map<IndexPath, int> units;

    // Load unit information.
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            IndexPath path {row, col};

            if (col < cols - 1) {
                FMAW::IO::fscanf(this->savefile, "%d ", &aux);
            } else {
                FMAW::IO::fscanf(this->savefile, "%d\n", &aux);
            }

            if (aux != UNIT_TYPE_EMPTY) units[path] = aux;
        }
    }

    FMAW::printf("Units loaded");

    // Load owner information.
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            IndexPath path {row, col};
            int type = units[path];

            if (col < cols - 1) {
                FMAW::IO::fscanf(this->savefile, "%d ", &aux);
            } else {
                FMAW::IO::fscanf(this->savefile, "%d\n", &aux);
            }

            if (aux != UNIT_OWNER_NONE) {
                FMAW::printf("Owner of this unit is %d", aux);
                Unit *u = Unit::UnitWithType(type, aux);
                this->cellAtIndexPath(path)->setCharacter(u);
            }
        }
    }

    FMAW::printf("Owners loaded");

    this->resetUnitMovements();

    int fr, fc, tr, tc;

    auto moveFollowingHistory = [this, &fr, &fc, &tr, &tc, callback](int ID) {
        FILE *f = this->savefile;
        if (FMAW::IO::fscanf(f, "%d %d %d %d\n", &fr, &fc, &tr, &tc) > 0) {
            if (fr == -1 && fc == -1 && tr == -1 && tc == -1) {
                FMAW::printf("\tTurn changed!");
                this->resetUnitMovements();
            } else {
                FMAW::printf("\tA movement has been loaded");
                IndexPath from = {fr, fc}, to = {tr, tc};

                if (!this->moveCharacterFromCellToCell(from, to, 200)) {
                    FMAW::printf("\tA unit has been attacked");
                    // If movement can't be done then it's an attack.
                    Unit *a = this->cellAtIndexPath(from)->getCharacter();
                    Unit *d = this->cellAtIndexPath(to)->getCharacter();
                    FMAW::Sound::playEffect(this->hitSoundID);
                    if (a->attackUnit(d)) {
                        FMAW::printf("\tA unit has been killed");
                        this->cellAtIndexPath(to)->setCharacter(nullptr);
                    }
                }
            }
        } else {
            FMAW::printf("\tFINISHED!");
            FMAW::Timer::dequeue_function(ID);
            FMAW::printf("\t\tDequeued");
            auto finish = [this, callback, ID](int finishCallbackID) {
                FMAW::IO::fclose(this->savefile);
                FMAW::printf("\t\tFile closed");
                this->playingSavedFile = false;
                FMAW::printf("\t\tPlaying state changed");
                this->savefile = nullptr;
                FMAW::printf("\t\tsaveFile set to null");
                this->clearGridUnits();
                FMAW::Tile::releaseAllSpriteMemory();
                FMAW::printf("\t\tMemory cleaned");
                this->initCursor();
                this->cursor.enable();
                this->setSquareCursor();
                FMAW::printf("\t\tCursor re-enabled");
                callback(true);
                FMAW::printf("\t\tCallback called");
            };
            FMAW::Timer::enqueue_function(finish, 5000, false);
        }
    };

    FMAW::Timer::enqueue_function(moveFollowingHistory, 1500, true);
}

void Grid::clearGridUnits() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath path {row, col};
            Cell *c = this->cellAtIndexPath(path);

            if (c->isOccupied()) {
                Unit *u = c->getCharacter();
                c->setCharacter(nullptr);
                delete u;
            }
        }
    }
}

bool Grid::isPlayingSavedFile() {
    return this->playingSavedFile;
}

bool Grid::isInteractionEnabled() {
    return (this->upArrowCallbackID == -1 ||
            this->rightArrowCallbackID == -1 ||
            this->leftArrowCallbackID == -1  ||
            this->downArrowCallbackID == -1 ||
            this->aButtonCallbackID == -1 ||
            this->bButtonCallbackID == -1);
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

bool Grid::attackCharacterAtCell(IndexPath attackerPos, IndexPath victimPos,
                                 unsigned int duration) {
    Cell *a = this->cellAtIndexPath(attackerPos);
    Cell *v = this->cellAtIndexPath(victimPos);
    if (v->isOccupied() && a->isOccupied() &&
            this->attackableCells[victimPos]) {
        Unit *attacker = a->getCharacter();
        Unit *victim = v->getCharacter();

        bool isKill = attacker->attackUnit(victim);
        attacker->decreaseAvailableActions();
        this->cursor.disable();

        std::function<void(bool)> reenableCursor = [this](bool b) {
            this->cursor.enable();
        };

        std::function<void(bool)> backToPosVict = [this, victim, v, duration,
        isKill, reenableCursor](bool b) {
            if (b && !isKill) {
                victim->animateToPosition(v->getCenter(), duration,
                                          reenableCursor);
            }
        };

        std::function<void(bool)> hurtRight = [victim, v, duration, isKill,
        backToPosVict](bool b) {
            FMAW::Point pvr = { v->getCenter().x + 5, v->getCenter().y };
            if (b && !isKill) {
                victim->animateToPosition(pvr, duration, backToPosVict);
            }
        };

        std::function<void(bool)> hurtLeft = [victim, v, duration, isKill,
        hurtRight](bool b) {
            FMAW::Point pvl = { v->getCenter().x - 5, v->getCenter().y };
            if (b && !isKill) {
                victim->animateToPosition(pvl, duration, hurtRight);
            }
        };

        std::function<void(bool)> backToPosAtt = [attacker, a, duration,
        hurtLeft, reenableCursor, isKill](bool b) {
            if (b) {
                if (!isKill) {
                    hurtLeft(b);
                } else {
                    reenableCursor(b);
                }

                attacker->animateToPosition(a->getCenter(), duration);
            }
        };

        attacker->animateToPosition(v->getCenter(), duration, backToPosAtt);

        return isKill;
    }
    return false;
}

bool Grid::moveCharacterFromCellToCell(IndexPath from, IndexPath to,
                                       unsigned int duration) {
    Cell *f = this->cellAtIndexPath(from);
    Cell *t = this->cellAtIndexPath(to);
    if (!t->isOccupied() && f->isOccupied() && this->reachableCells[to]) {
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
        this->recomputeVisibleCells();
        return true;
    }
    return false;
}

bool Grid::canMoveCharacterFromCellToCell(IndexPath from, IndexPath to) {
    if (to.row < 0 || to.row >= this->rows ||
            to.col < 0 || to.col > this->cols) {
        return false;
    }

    Cell *f = this->cellAtIndexPath(from);
    Cell *t = this->cellAtIndexPath(to);

    if (!t->isOccupied() && f->isOccupied()) {
        Unit *u = f->getCharacter();
        if (u->getOwner() == TurnManager::currentPlayerID()) {
            if (this->getSelectedPath().row != from.row ||
                    this->getSelectedPath().col != from.col) {
                this->selectCellAtIndexPath(from);
                this->recomputeReachableCells();
            }
            return this->reachableCells[to];
        }
    }

    return false;
}

void Grid::renderBackground() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath p{row, col};
            if (this->visibleCells[p]) {
                this->cellAtIndexPath(p)->renderBackground();
            } else {
                this->cellAtIndexPath(p)->renderFoggyBackground();
            }
        }
    }
}

void Grid::renderCharacters() {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath p{row, col};
            if (this->visibleCells[p]) {
                this->cellAtIndexPath(p)->renderCharacter();
            }
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

bool Grid::existCharacterWithOwner(int owner) {
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath p{row, col};
            Cell *c = this->cellAtIndexPath(p);
            Unit *u = c->getCharacter();
            if (c->isOccupied() && u->getOwner() == owner) {
                FMAW::printf("Enemy at %d %d", row, col);
                return true;
            }
        }
    }
    return false;
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
            Cell *c = this->cellAtSelectedPath();

            // Set cursor based on movement capability.
            if (this->reachableCells[this->selectedPath]) {
                if (c->isOccupied()) {
                    Unit *u = c->getCharacter();
                    if (u->getOwner() == TurnManager::currentPlayerID()) {
                        this->setSquareCursor();
                        FMAW::Sound::playEffect(this->selectSoundID);
                    } else {
                        this->setCrossCursor();
                    }
                } else {
                    this->setArrowCursor();
                    FMAW::Sound::playEffect(this->selectSoundID);
                }
            } else {
                this->setCrossCursor();
                FMAW::Sound::playEffect(this->forbiddenSoundID);
            }

            // If we can attack that player then we set proper cursor.
            if (this->attackableCells[this->selectedPath]) {
                if (c->isOccupied()) {
                    Unit *u = c->getCharacter();
                    if (u->getOwner() != TurnManager::currentPlayerID()) {
                        this->setSwordCursor();
                        FMAW::Sound::playEffect(this->selectSoundID);
                    }
                }
            }
        } else {
            Cell *c = this->cellAtSelectedPath();
            if (c->isOccupied() && !c->getCharacter()->hasAvailableActions()) {
                this->setCrossCursor();
            } else if (c->isOccupied() &&
                       c->getCharacter()->getOwner() !=
                       TurnManager::currentPlayerID()) {
                this->setCrossCursor();
                FMAW::Sound::playEffect(this->forbiddenSoundID);
            } else {
                this->setSquareCursor();
                FMAW::Sound::playEffect(this->selectSoundID);
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

void Grid::setSwordCursor() {
    this->cursor.setSword();
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
    this->recomputeVisibleCells();

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
            FMAW::Sound::playEffect(this->selectSoundID);
            this->setArrowCursor();
            FMAW::printf("Se ha marcado la celda %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col);
            this->recomputeReachableCells();
            this->recomputeAttackableCells();
        } else if (c->isOccupied() && u->getOwner() !=
                   TurnManager::currentPlayerID()) {
            // If cell is occupied by a character owned by an enemy we release
            // previously picked up cell and we reset the cursor.
            FMAW::printf("Hay un enemigo en la celda %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col);
            if (this->hasPickedUpCell() &&
                    this->attackableCells[this->getSelectedPath()]) {
                FMAW::Sound::playEffect(this->hitSoundID);
                FMAW::printf("Atacando enemigo en la celda %d %d",
                             this->pickedUpCell.row,
                             this->pickedUpCell.col);

                bool isKill = this->attackCharacterAtCell(this->pickedUpCell,
                              this->getSelectedPath(),
                              50);

                if (isKill) {
                    FMAW::printf("Enemigo abatido!");
                    // We save death in history log.
                    if (this->savefile != nullptr) {
                        FMAW::IO::fprintf(this->savefile, "%d %d %d %d\n",
                                          this->pickedUpCell.row,
                                          this->pickedUpCell.col,
                                          this->getSelectedPath().row,
                                          this->getSelectedPath().col);
                        FMAW::IO::fflush(this->savefile);
                    }
                    int enemyID = u->getOwner();
                    c->setCharacter(nullptr);
                    if (!this->existCharacterWithOwner(enemyID)) {
                        this->gameOverCallback(TurnManager::currentPlayerID());
                    }
                } else {
                    FMAW::printf("El enemigo sigue vivo");
                }
            } else {
                FMAW::Sound::playEffect(this->forbiddenSoundID);
            }
            this->resetPickedUpCell();
            this->setCrossCursor();
        } else if (this->hasPickedUpCell() &&
                   this->reachableCells[this->getSelectedPath()]) {
            // If there is a picked up cell and we can move to selected cell
            // then we move the character and reset picked up cell.
            FMAW::printf("Se mueve de %d %d a %d %d",
                         this->pickedUpCell.row,
                         this->pickedUpCell.col,
                         this->getSelectedPath().row,
                         this->getSelectedPath().col);
            FMAW::Sound::playEffect(this->selectSoundID);
            this->moveCharacterFromCellToCell(this->pickedUpCell,
                                              this->getSelectedPath(), 100);
            u->decreaseAvailableActions();
            if (!u->hasAvailableActions()) {
                this->setCrossCursor();
            } else {
                this->recomputeAttackableCells();
            }
            this->resetPickedUpCell();
        }
    };
    if (this->aButtonCallbackID == -1) {
        this->aButtonCallbackID = FMAW::Input::onButtonAReleased(releaseA);
    }

    auto releaseB = [this]() {
        if (this->savefile != nullptr) {
            FMAW::IO::fprintf(this->savefile, "-1 -1 -1 -1\n");
            FMAW::IO::fflush(this->savefile);
        }
    };
    if (this->bButtonCallbackID == -1) {
        this->bButtonCallbackID = FMAW::Input::onButtonAReleased(releaseB);
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
    if (this->bButtonCallbackID != -1) {
        FMAW::Input::unregisterCallback(this->bButtonCallbackID);
        this->bButtonCallbackID = -1;
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

void Grid::recomputeAttackableCells() {
    this->attackableCells.clear();

    if (this->pickedUpCell.row == -1 || this->pickedUpCell.col == -1) {
        for (int row = 0; row < this->rows; row++) {
            for (int col = 0; col < this->cols; col++) {
                this->attackableCells[ {row, col}] = false;
            }
        }
    } else {
        Cell *cell = this->cellAtIndexPath(this->pickedUpCell);
        Unit *unit = cell->getCharacter();
        int minAttack = unit->getMinimumAttackRange();
        int maxAttack = unit->getMaximumAttackRange();

        // First no cell is attackable.
        for (int row = 0; row < this->rows; row++) {
            for (int col = 0; col < this->cols; col++) {
                this->attackableCells[ {row, col}] = false;
            }
        }

        for (int attRan = minAttack; attRan <= maxAttack; attRan++) {
            int col = this->pickedUpCell.col - attRan;
            for (int row = 0; row < attRan; row++, col++) {
                if (col >= 0 && col < this->cols - 1) {
                    if (this->pickedUpCell.row >= row) {
                        this->attackableCells[ {
                            this->pickedUpCell.row - row,
                            col
                        }] = true;
                    }
                    if (this->pickedUpCell.row < this->rows - row) {
                        this->attackableCells[ {this->pickedUpCell.row + row,
                                                col
                                               }] = true;
                    }
                }
            }
            for (int row = attRan; row >= 0; row--, col++) {
                if (col >= 0 && col < this->cols - 1) {
                    if (this->pickedUpCell.row >= row) {
                        this->attackableCells[ {this->pickedUpCell.row - row,
                                                col
                                               }] = true;
                    }
                    if (this->pickedUpCell.row < this->rows - row) {
                        this->attackableCells[ {
                            this->pickedUpCell.row + row,
                            col
                        }] = true;
                    }
                }
            }
        }
    }
}

void Grid::recomputeVisibleCells() {
    this->visibleCells.clear();

    std::vector<IndexPath> units{};

    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            IndexPath p{row, col};
            Cell *c = this->cellAtIndexPath(p);
            Unit *u = c->getCharacter();
            if (c->isOccupied() &&
                    u->getOwner() == TurnManager::currentPlayerID()) {
                units.push_back(p);
            }
        }
    }

    // First no cell is visible.
    for (int row = 0; row < this->rows; row++) {
        for (int col = 0; col < this->cols; col++) {
            this->visibleCells[ {row, col}] = false;
        }
    }

    for (IndexPath p : units) {
        Cell *cell = this->cellAtIndexPath(p);
        Unit *unit = cell->getCharacter();
        int maxSight = unit->getSightDistance();

        std::map<IndexPath, int> reachCost;

        // First no cell is visible.
        for (int row = 0; row < this->rows; row++) {
            for (int col = 0; col < this->cols; col++) {
                reachCost[ {row, col}] = COST_CELL_INFINITY;
            }
        }

        // Only cell reachable is the first one.
        reachCost[p] = 0;
        this->visibleCells[p] = true;

        // When the cost of a cell changes we explore its neighbours.
        std::queue<IndexPath> pathsToCheck({ p });

        // While we have some cell to check we check it...
        while (pathsToCheck.size() > 0) {
            IndexPath path = pathsToCheck.front();  // Cell to check.
            pathsToCheck.pop();  // We remove it as we have checked it.
            // If we go up...
            if (path.row > 0) {
                IndexPath u = { path.row - 1, path.col };
                int c = this->cellAtIndexPath(u)->sightCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[u] && newCost <= maxSight) {
                    reachCost[u] = newCost;
                    this->visibleCells[u] = true;
                    pathsToCheck.push(u);
                }
            }
            // If we go down...
            if (path.row < this->rows - 1) {
                IndexPath d = { path.row + 1, path.col };
                int c = this->cellAtIndexPath(d)->sightCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[d] && newCost <= maxSight) {
                    reachCost[d] = newCost;
                    this->visibleCells[d] = true;
                    pathsToCheck.push(d);
                }
            }
            // If we go left...
            if (path.col > 0) {
                IndexPath l = { path.row, path.col - 1 };
                int c = this->cellAtIndexPath(l)->sightCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[l] && newCost <= maxSight) {
                    reachCost[l] = newCost;
                    this->visibleCells[l] = true;
                    pathsToCheck.push(l);
                }
            }
            // If we go right...
            if (path.col < this->cols - 1) {
                IndexPath r = { path.row, path.col + 1 };
                int c = this->cellAtIndexPath(r)->sightCost();
                int newCost = reachCost[path] + c;
                if (newCost < reachCost[r] && newCost <= maxSight) {
                    reachCost[r] = newCost;
                    this->visibleCells[r] = true;
                    pathsToCheck.push(r);
                }
            }
        }
    }

    this->renderBackground();
}
