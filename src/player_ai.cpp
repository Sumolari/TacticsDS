// Copyright 2015 FMAW

#include "./player_ai.h"

#include <cstdlib>
#include <vector>

#include "./unit.h"
#include "./cell.h"
#include "./turnManager.h"

#include "./FMAW.h"

PlayerAI::PlayerAI(Grid *grid, std::function<void(void)> callback) :
    grid(grid),
    onFinishTurnCallback(callback),
    seed(42) {}

PlayerAI::PlayerAI(Grid *grid, std::function<void(void)> callback,
                   PlayerID ID) :
    Player(ID),
    grid(grid),
    onFinishTurnCallback(callback),
    seed(42) {}

void PlayerAI::startTurn() {
    // Prevent user from interacting with grid.
    this->grid->dequeueCallbacks();

    IndexPath previousPositionOfCursor = this->grid->getSelectedPath();

    // Here we will store the units of this AI player and the path where they
    // are located.
    std::vector<Unit *> units;
    std::vector<IndexPath> paths;
    // We have to check the full grid to know where are our units.
    for (int row = 0; row < this->grid->numRows(); row++) {
        for (int col = 0; col < this->grid->numCols(); col++)  {
            IndexPath path = { row, col };
            Cell *c = this->grid->cellAtIndexPath(path);
            if (c->isOccupied()) {
                Unit *u = c->getCharacter();
                if (u->getOwner() == this->ID) {
                    units.push_back(u);
                    paths.push_back(path);
                }
            }
        }
    }

    // Just to scare the other player.
    FMAW::printf("Turn of AI player %d, MUA-HAHAHA-HA", this->ID);
    FMAW::printf("\tI've %d units", units.size());

    // We will call the following callback once each 1.5s.
    this->unitNumber = 0;
    auto moveSomeUnit = [this, units, paths, previousPositionOfCursor](int ID) {
        if (this->unitNumber < units.size()) {
            //------------------------------------------------------------------
            // Actual AI script.
            //------------------------------------------------------------------
            IndexPath path = paths[this->unitNumber];
            Unit *unit = units[this->unitNumber];

            int row = path.row;
            int col = path.col;

            FMAW::printf("Choosing action for unit %d at %d %d",
                         this->unitNumber, row, col);

            std::vector<IndexPath> availableMovements;

            IndexPath up = { row - 1, col };
            IndexPath down = { row + 1, col };
            IndexPath left = { row, col - 1 };
            IndexPath right = { row, col + 1 };

            std::vector<IndexPath> candidates({up, down, left, right});

            for (auto it = candidates.begin(); it != candidates.end(); it++)
                if (this->grid->canMoveCharacterFromCellToCell(path, *it))
                    availableMovements.push_back(*it);

            int movement = rand_r(&(this->seed)) % availableMovements.size();
            IndexPath chosen = availableMovements[movement];

            this->grid->moveCharacterFromCellToCell(path, chosen, 200);
            //------------------------------------------------------------------
            // End of AI script.
            //------------------------------------------------------------------
            this->unitNumber++;
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
