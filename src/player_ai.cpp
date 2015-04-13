// Copyright 2015 FMAW

#include "./player_ai.h"

#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>

#include "./constants.h"
#include "./unit.h"
#include "./cell.h"
#include "./turnManager.h"

#include "./FMAW.h"

#include <algorithm>

PlayerAI::PlayerAI(Grid *grid, std::function<void(void)> callback) :
    grid(grid),
    onFinishTurnCallback(callback),
    seed(42) {}

PlayerAI::PlayerAI(Grid *grid, std::function<void(void)> call, PlayerID ID) :
    Player(ID),
    grid(grid),
    onFinishTurnCallback(call),
    seed(42) {}

void PlayerAI::startTurn() {

    // Prevent user from interacting with grid.
    this->grid->dequeueCallbacks();

    IndexPath previousPositionOfCursor = this->grid->getSelectedPath();

    bool recompute = true;
    std::map<IndexPath, int> distanceToNearestEnemyUnit;

    // Helper function to compute best cell to move.
    auto nearestEnemy = [&distanceToNearestEnemyUnit](IndexPath i, IndexPath j)
    -> bool {
        return distanceToNearestEnemyUnit[i] < distanceToNearestEnemyUnit[j];
    };

    // Now we have to make some decisions...
    // We will call the following callback once each 1.5s.
    this->unitNumber = 0;
    auto moveSomeUnit = [this, previousPositionOfCursor, &recompute,
    &distanceToNearestEnemyUnit, nearestEnemy](int ID) {
        FMAW::printf("Computing AI data...");
        // Here we will store the units of this AI player and the path where
        // they are located.
        std::vector<Unit *> IAunits;
        std::vector<IndexPath> IApaths;
        std::vector<Unit *> playerUnits;
        std::vector<IndexPath> playerPaths;
        std::vector<IndexPath> chosenPaths;

        // We have to check the full grid to know where are our units.
        for (int row = 0; row < this->grid->numRows(); row++) {
            for (int col = 0; col < this->grid->numCols(); col++)  {
                IndexPath path = { row, col };
                Cell *c = this->grid->cellAtIndexPath(path);
                if (c->isOccupied()) {
                    Unit *u = c->getCharacter();
                    if (u->getOwner() == this->ID) {
                        IAunits.push_back(u);
                        IApaths.push_back(path);
                    } else {
                        playerUnits.push_back(u);
                        playerPaths.push_back(path);
                    }
                }
            }
        }

        FMAW::printf("\tReady units");

        std::map<IndexPath, std::vector<IndexPath>> IAUnitCanAttack;
        std::map<IndexPath, std::vector<IndexPath>> PlayerUnitCanBeAttackedBy;

        // Compute which units can attack which ones.
        for (IndexPath p : IApaths) {
            this->grid->setPickedUpCell(p);
            Cell *c = this->grid->cellAtIndexPath(p);
            if (c->getCharacter()->hasAvailableActions()) {
                for (IndexPath t : playerPaths) {
                    if (grid->pickedUpUnitCanAttackCharacterAtCell(t)) {
                        IAUnitCanAttack[p].push_back(t);
                        PlayerUnitCanBeAttackedBy[t].push_back(p);
                    }
                }
            }
        }

        FMAW::printf("\tReady attacks");

        if (recompute) {
            // Compute distance to nearest visible enemy.
            for (int row = 0; row < this->grid->numRows(); row++) {
                for (int col = 0; col < this->grid->numCols(); col++) {
                    IndexPath f = { row, col };
                    Cell *from = grid->cellAtIndexPath(f);
                    distanceToNearestEnemyUnit[f] = COST_CELL_INFINITY;
                    for (int tr = 0; tr < this->grid->numRows(); tr++) {
                        for (int tc = 0; tc < this->grid->numCols(); tc++) {
                            IndexPath t = { tr, tc };
                            Cell *to = this->grid->cellAtIndexPath(t);
                            int distance = abs(t.row - f.row) +
                                           abs(t.col - f.col);
                            if (to->isOccupied()) {
                                Unit *u = to->getCharacter();
                                if (this->grid->canSeeCharacterAtCell(t) &&
                                        u->getOwner() != this->ID) {
                                    distanceToNearestEnemyUnit[f] = distance;
                                }
                            }
                        }
                    }
                }
            }
            recompute = false;
        }

        FMAW::printf("\tReady distances");

        bool canDoSomething = false;
        for (Unit *u : IAunits) {
            if (u->hasAvailableActions()) {
                canDoSomething = true;
            }
        }
        if (canDoSomething) {
            while (!IAunits[this->unitNumber]->hasAvailableActions()) {
                this->unitNumber++;
                this->unitNumber %= IAunits.size();
            }
            //------------------------------------------------------------------
            // Actual AI script.
            //------------------------------------------------------------------
            bool actionDone = false;
            IndexPath path = IApaths[this->unitNumber];
            Unit *unit = IAunits[this->unitNumber];
            this->grid->setPickedUpCell(path);

            int row = path.row;
            int col = path.col;

            FMAW::printf("Choosing action for unit %d at %d %d",
                         this->unitNumber, row, col);

            std::vector<IndexPath> shouldAttack;
            std::vector<IndexPath> attackable;

            // If I'm the only one who can attack, I'll do (random on tie).

            attackable = IAUnitCanAttack[path];
            for (IndexPath t : attackable) {
                if (PlayerUnitCanBeAttackedBy[t].size() == 1) {
                    shouldAttack.push_back(t);
                }
            }

            FMAW::printf("\tI'm the only one that can attack %d units",
                         attackable.size());

            // If I'm not the only one, I attack to a random (random on tie).
            if (shouldAttack.size() == 0) {
                attackable = IAUnitCanAttack[path];
                for (IndexPath t : attackable) {
                    shouldAttack.push_back(t);
                }

                FMAW::printf("\tMe and others can attack %d units",
                             attackable.size());
            }

            // I'll attack if I can.
            if (shouldAttack.size() > 0) {
                while (shouldAttack.size() > 0) {
                    int rand = rand_r(&(this->seed)) % shouldAttack.size();
                    IndexPath tg = shouldAttack[rand];
                    if (this->grid->pickedUpUnitCanAttackCharacterAtCell(tg)) {
                        FMAW::printf("\tWill attack unit at %d %d",
                                     tg.row, tg.col);
                        bool kill = this->grid->attackCharacterAtCell(
                                        path, tg, ATTACK_DURATION);
                        if (kill) {
                            recompute = true;
                        }
                        actionDone = true;
                        break;
                    } else {
                        FMAW::printf("\tCouldn't to attack unit at %d %d",
                                     tg.row, tg.col);
                        shouldAttack.erase(shouldAttack.begin() + rand);
                    }
                }
            }

            // If I can't attack, I'll move to the nearest enemy unit (random
            // on tie).
            if (!actionDone) {
                FMAW::printf("\tI couldn't attack any unit, so I'll move");
                std::vector<IndexPath> availableMovements;
                for (int r = 0; r < this->grid->numRows(); r++) {
                    for (int c = 0; c < this->grid->numCols(); c++) {
                        IndexPath t = { r, c };
                        if (this->grid->canMoveCharacterFromCellToCell(path, t)) {
                            availableMovements.push_back(t);
                        }
                    }
                }

                FMAW::printf("\tI can move to %d cells",
                             availableMovements.size());

                std::sort(availableMovements.begin(), availableMovements.end(),
                          nearestEnemy);

                if (availableMovements.size() > 0) {
                    IndexPath chosen = availableMovements[0];
                    FMAW::printf("\tI'll move to %d %d",
                                 chosen.row, chosen.col);
                    this->grid->moveCharacterFromCellToCell(path, chosen,
                                                            MOVEMENT_DURATION);
                    IApaths[this->unitNumber] = chosen;
                }
            }

            FMAW::printf("\t-------------------------------------------------");

            //------------------------------------------------------------------
            // End of AI script.
            //------------------------------------------------------------------
            this->grid->selectCellAtIndexPath(previousPositionOfCursor);
        } else {
            FMAW::printf("\tI've finished!");
            this->grid->enqueueCallbacks();
            FMAW::Timer::dequeue_function(ID);
            this->onFinishTurnCallback();
        }
    };
    FMAW::Timer::enqueue_function(moveSomeUnit, 1500, true);
}

void PlayerAI::print() {
    FMAW::printf("I'm an AI player with ID=%d", this->ID);
}
