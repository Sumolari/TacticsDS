// Copyright 2015 FMAW

#include "./player_ai.h"

#include <cstdlib>
#include <vector>

#include "./unit.h"
#include "./cell.h"
#include "./turnManager.h"

#include "./FMAW.h"

#include <algorithm>

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

void releaseUnitAtCell( IndexPath attackCoordinate, std::vector<IndexPath>& playerPaths,
  std::vector<Unit *>& playerUnits ){
  for( uint i = 0; i < playerPaths.size(); i++){
    if (playerPaths[i].row == attackCoordinate.row &&
      playerPaths[i].col == attackCoordinate.col ) {
      playerPaths.erase( playerPaths.begin() + i);
      playerUnits.erase( playerUnits.begin() + i);
      break;
    }
  }
}

bool custFind( std::vector<IndexPath>& pathsToCheck, IndexPath check ){

    for( uint i = 0; i < pathsToCheck.size(); i++){
      FMAW::printf("pathsToCheck row:%d, col:%d", pathsToCheck[i].row, pathsToCheck[i].col);
      if (pathsToCheck[i].row == check.row && pathsToCheck[i].col == check.col )
        return true;
    }
    return false;
}

IndexPath PlayerAI::getAttackCoordinate( int minDistance, int maxDistance, IndexPath origin,
  std::vector<IndexPath> playerPaths, Unit *currentUnit){

  //FMAW::printf("ORIGIN ROW %d, COL %d",  origin.row, origin.col);
  //FMAW::printf("MINDISTANCE %d, MAXDISTANCE %d", minDistance, maxDistance );
  int leftLimit = std::max( 0, origin.col - maxDistance );
  int rightLimit = std::min( this->grid->numCols(), origin.col + maxDistance );
  int upLimit = std::max( 0, origin.row - maxDistance );
  int downLimit = std::min( this->grid->numRows(), origin.row + maxDistance );

  int leftInnerLimit = std::max( 0, origin.col - minDistance );
  int rightInnerLimit = std::min( this->grid->numCols(), origin.col + minDistance );
  int upInnerLimit = std::max( 0, origin.row - minDistance );
  int downInnerLimit = std::min( this->grid->numRows(), origin.row + minDistance );

  //FMAW::printf("upLimit %d downLimit %d leftlimit %d, rightLimit %d",
  //  upLimit, downLimit, leftLimit, rightLimit );

  for( int i = upLimit; i <= downLimit; i++ ){
    for( int j = leftLimit; j <= rightLimit; j++){

      int distance = abs(i - origin.row) + abs(j - origin.col);
      if( distance >= minDistance && distance <= maxDistance && custFind( playerPaths, {i, j})) {
        return {i, j};
      }
    }
  }

  FMAW::printf("RETORNO -1");
  return {-1, -1};
}

IndexPath PlayerAI::getClosestPath ( IndexPath origin, std::vector<IndexPath> enemies,
                                std::vector<IndexPath>& takenPaths){
    IndexPath minPath;
    int minDistance = 9999;

    FMAW::printf("Ejecuto getClosestPath");
    for( uint i = 0; i < enemies.size(); i++){
        for (int row = 0; row < this->grid->numRows(); row++) {
            for (int col = 0; col < this->grid->numCols(); col++) {
                IndexPath check = { row, col };
                //FMAW::printf("\tCurrently in row:%d, col:%d", check.row, check.col);
                if(this->grid->canMoveCharacterFromCellToCell(origin, check) &&
                    !custFind( takenPaths, check )){
                    int distance = abs(enemies[i].row - row) + abs(enemies[i].col - col);
                    if( distance < minDistance){
                        FMAW::printf("Selecciono nuevo path row:%d, col:%d", check.row, check.col);
                        minDistance = distance;
                        minPath = check;
                    }
                }
            }
        }
    }

    takenPaths.push_back( minPath );

    FMAW::printf("Print the takenPaths vector in getClosestPath");
    return minPath;
}

void PlayerAI::startTurn() {

    // Prevent user from interacting with grid.
    this->grid->dequeueCallbacks();

    IndexPath previousPositionOfCursor = this->grid->getSelectedPath();

    // Here we will store the units of this AI player and the path where they
    // are located.
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

    std::vector<IndexPath> attackPositions;

    for (uint i = 0; i < IAunits.size(); i++) {
        this->grid->setPickedUpCell(IApaths[i]);

      Unit *currentUnit = IAunits[i];

      IndexPath attackCoordinate = getAttackCoordinate( currentUnit->getMinimumAttackRange(),
        currentUnit->getMaximumAttackRange(), IApaths[i], playerPaths, currentUnit);

      attackPositions.push_back( attackCoordinate );

      if( attackCoordinate.row != -1){
        FMAW::printf("Estoy en la celda row:%d, col:%d", IApaths[i].row, IApaths[i].col);
        FMAW::printf("TENGO QUE ATACAR A CELDA row:%d, col:%d", attackCoordinate.row, attackCoordinate.col);
        while( IAunits[i]->hasAvailableActions()) {
          FMAW::printf("ATACO");
          if ( this->grid->attackCharacterAtCell(IApaths[i], attackCoordinate, 50) ) {
            releaseUnitAtCell( attackCoordinate, playerPaths, playerUnits );
            break;
          }
        }
      } else {
        FMAW::printf("NO ATACO");
      }
      FMAW::printf("--------------------------------");
    }


    //for( uint i = 0; i < IAunits.size(); i++){
    //FMAW::printf("--------------------------------");
    //if( attackPositions[i].row != -1){
    //  FMAW::printf("Estoy en la celda row:%d, col:%d", IApaths[i].row, IApaths[i].col);
    //  FMAW::printf("TENGO QUE ATACAR A CELDA row:%d, col:%d", attackPositions[i].row, attackPositions[i].col);
    //  while( IAunits[i]->hasAvailableActions()) {
    //    FMAW::printf("ATACO");
    //    this->grid->attackCharacterAtCell(IApaths[i], attackPositions[i], 50);
    //  }
    //  //FMAW::printf("Estoy en la celda row:%d, col:%d", IApaths[i].row, IApaths[i].col);
    //  //FMAW::printf("TENGO QUE ATACAR A CELDA row:%d, col:%d", attackCoordinate.row, attackCoordinate.col);
    //  //while( currentUnit->hasAvailableActions()) {
    //  //  FMAW::printf("ATACO");
    //  //  this->grid->attackCharacterAtCell(IApaths[i], attackCoordinate, 50);
    //  //}
//
    //  //IAunits.erase( IAunits.begin()+i );
    //  //IApaths.erase( IApaths.begin()+i );
    //  //i--;
    //} else {
    //  FMAW::printf("NO ATACO");
    //}
    //  FMAW::printf("--------------------------------");
    //}




    //// Just to scare the other player.
    //FMAW::printf("Turn of AI player %d, GET REKT SON", this->ID);
    //FMAW::printf("\tI've %d units", IAunits.size());
//
    ////std::vector<std::pair<Unit *, std::vector<IndexPath>>> availableMovementsUnits;
    //std::vector<IndexPath> takenPaths;
    //// Loop to check possible movements.
//
    //for( uint i = 0; i < IAunits.size(); i++){
//
    //  IndexPath path = IApaths[ i ];
    //  this->grid->setPickedUpCell( path.row, path.col );
    //  this->grid->recomputeReachableCells();
    //  this->grid->recomputeAttackableCells();
    //  FMAW::printf("Possible movements %d", i);
    //  chosenPaths.push_back( getClosestPath( path, playerPaths, takenPaths) );
    //}
//
    //this->unitNumber = 0;
    //auto moveSomeUnit = [this, IAunits, IApaths, chosenPaths, previousPositionOfCursor](int ID) {
    //  if (this->unitNumber < IAunits.size()) {
    //      //------------------------------------------------------------------
    //      // Actual AI script.
    //      //------------------------------------------------------------------
    //      IndexPath path = IApaths[this->unitNumber];
    //      Unit *unit = IAunits[this->unitNumber];
//
    //      IndexPath chosen = chosenPaths[this->unitNumber];
//
    //      FMAW::printf("Checking selected path row:%d col:%d", chosen.row, chosen.col);
    //      this->grid->moveCharacterFromCellToCell(path, chosen, 200);
    //      //------------------------------------------------------------------
    //      // End of AI script.
    //      //------------------------------------------------------------------
    //      this->unitNumber++;
    //      this->grid->selectCellAtIndexPath(previousPositionOfCursor);
    //  } else {
    //      FMAW::printf("\tI've finished!");
    //      this->grid->enqueueCallbacks();
    //      FMAW::Timer::dequeue_function(ID);
    //      this->onFinishTurnCallback();
    //  }
    //};
    //FMAW::Timer::enqueue_function(moveSomeUnit, 1500, true);

    // We will call the following callback once each 1.5s.
    //this->unitNumber = 0;
    //auto moveSomeUnit = [this, units, IApaths, previousPositionOfCursor](int ID) {
    //    if (this->unitNumber < units.size()) {
    //        //------------------------------------------------------------------
    //        // Actual AI script.
    //        //------------------------------------------------------------------
    //        IndexPath path = paths[this->unitNumber];
    //        Unit *unit = units[this->unitNumber];
//
    //        int row = path.row;
    //        int col = path.col;
//
    //        FMAW::printf("Choosing action for unit %d at %d %d",
    //                     this->unitNumber, row, col);
//
    //        std::vector<IndexPath> availableMovements;
//
    //        IndexPath up = { row - 1, col };
    //        IndexPath down = { row + 1, col };
    //        IndexPath left = { row, col - 1 };
    //        IndexPath right = { row, col + 1 };
//
    //        std::vector<IndexPath> candidates({up, down, left, right});
//
    //        for (auto it = candidates.begin(); it != candidates.end(); it++)
    //            if (this->grid->canMoveCharacterFromCellToCell(path, *it))
    //                availableMovements.push_back(*it);
//
    //        int movement = rand_r(&(this->seed)) % availableMovements.size();
    //        IndexPath chosen = availableMovements[movement];
//
    //        this->grid->moveCharacterFromCellToCell(path, chosen, 200);
    //        //------------------------------------------------------------------
    //        // End of AI script.
    //        //------------------------------------------------------------------
    //        this->unitNumber++;
    //        this->grid->selectCellAtIndexPath(previousPositionOfCursor);
    //    } else {
    //        FMAW::printf("\tI've finished!");
    //        this->grid->enqueueCallbacks();
    //        FMAW::Timer::dequeue_function(ID);
    //        this->onFinishTurnCallback();
    //    }
    //};
    //FMAW::Timer::enqueue_function(moveSomeUnit, 1500, true);
    FMAW::printf("\tI've finished!");

    this->grid->enqueueCallbacks();
    FMAW::Timer::dequeue_function(ID);
    this->onFinishTurnCallback();
}

void PlayerAI::print() {
    FMAW::printf("I'm an AI player with ID=%d", this->ID);
}
