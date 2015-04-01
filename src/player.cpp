// Copyright 2015 FMAW

#include "./player.h"

#include "./turnManager.h"

#include "./FMAW.h"

Player::Player(): ID(TurnManager::numPlayers()) {}

Player::Player(PlayerID ID): ID(ID) {}

PlayerID Player::getID() {
    return this->ID;
}

void Player::startTurn() {
    FMAW::printf("Turn of player %d", this->ID);
}

void Player::print() {
    FMAW::printf("I'm a human player with ID=%d", this->ID);
}
