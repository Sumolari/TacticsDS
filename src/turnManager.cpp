// Copyright 2015 FMAW

#include "./turnManager.h"
#include <vector>
#include "./FMAW.h"
#include "./player_ai.h"

namespace TurnManager {

// ID of currently playing player.
PlayerID _currentPlayerID = 0;

// ID of winner player.
PlayerID _winnerID = -1;

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
    resetWinner();
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

PlayerID getWinner() {
    return _winnerID;
}

void setWinner(PlayerID winnerID) {
    _winnerID = winnerID;
}

void resetWinner() {
    _winnerID = -1;
}

bool AIPlaying() {
    return (dynamic_cast<PlayerAI *>(players[_currentPlayerID]) != NULL);
}

}  // namespace TurnManager
