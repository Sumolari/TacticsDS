// Copyright 2015 FMAW

#include "./unit.h"

#include "./FMAW.h"

#include "./constants.h"
#include "./warrior.h"

Unit::Unit(PlayerID ownerID) : Unit(FMAW::Sprite(), ownerID) {}

Unit::Unit(FMAW::Sprite sprite): Unit(sprite, 0) {}

Unit::Unit(FMAW::Sprite sprite, PlayerID ownerID) :
    Character(sprite),
    ownerID(ownerID) {
    init();
}

Unit *Unit::UnitWithType(int unitType, PlayerID ownerID) {
    switch (unitType) {
        case UNIT_TYPE_WARRIOR:
            return new Warrior(ownerID);
        default:
            return new Unit(ownerID);
    }
}

void Unit::init() {}

void Unit::update() {}

int Unit::getUnitType() {
    return this->unitType;
}

void Unit::resetAvailableActions() {
    this->currentAvailableActions = this->maximumAvailableActions;
}

void Unit::decreaseAvailableActions() {
    this->currentAvailableActions--;
    if (this->currentAvailableActions < 0) {
        this->currentAvailableActions = 0;
    }
}

bool Unit::hasAvailableActions() {
    /*
    FMAW::printf("This unit has %d actions available",
                 this->currentAvailableActions);
    */
    return this->currentAvailableActions > 0;
}

int Unit::getMovementCapacity() {
    return this->movementCapacity;
}

PlayerID Unit::getOwner() {
    return this->ownerID;
}

PlayerID Unit::setOwner(PlayerID owner) {
    PlayerID prev = this->ownerID;
    this->ownerID = owner;
    return prev;
}
