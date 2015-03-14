// Copyright 2015 FMAW

#include "./player.h"

#include "./turnManager.h"

#include "./FMAW.h"

Player::Player(): ID(TurnManager::numPlayers()) {}

PlayerID Player::getID() {
    return this->ID;
}

void Player::startTurn() {
    FMAW::printf("Turn of player %d", this->ID);
}
