// Copyright 2015 FMAW

#include "./unit.h"

Unit::Unit(PlayerID ownerID) : Unit(FMAW::Sprite(), ownerID) {}

Unit::Unit(FMAW::Sprite sprite): Unit(sprite, 0) {}

Unit::Unit(FMAW::Sprite sprite, PlayerID ownerID) :
    Character(sprite),
    ownerID(ownerID) {
    init();
}

void Unit::init() {}

void Unit::update() {}

PlayerID Unit::getOwner() {
    return this->ownerID;
}
