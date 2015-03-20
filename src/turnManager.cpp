// Copyright 2015 FMAW

#include "./turnManager.h"
#include <vector>
#include "./FMAW.h"


namespace TurnManager {

// ID of currently playing player.
PlayerID _currentPlayerID = 0;

// Players in the game.
std::vector<Player *> players;

void addPlayer(Player *player) {
    players.push_back(player);
}

PlayerID currentPlayerID() {
    return _currentPlayerID;
}

int numPlayers() {
    return players.size();
}

void reset() {
    _currentPlayerID = 0;
    players.clear();
}

void finishTurn() {
    _currentPlayerID++;
    _currentPlayerID %= numPlayers();
    players[_currentPlayerID]->print();
    players[_currentPlayerID]->startTurn();
}

bool gameShouldFinish() {
    return false;
}

}  // namespace TurnManager
