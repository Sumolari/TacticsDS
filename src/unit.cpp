// Copyright 2015 FMAW

#include "./unit.h"

#include "./FMAW.h"

Unit::Unit(PlayerID ownerID) : Unit(FMAW::Sprite(), ownerID) {}

Unit::Unit(FMAW::Sprite sprite): Unit(sprite, 0) {}

Unit::Unit(FMAW::Sprite sprite, PlayerID ownerID) :
    Character(sprite),
    ownerID(ownerID) {
    init();
}

void Unit::init() {}

void Unit::update() {}

void Unit::resetAvailableActions() {
    FMAW::printf("RESET");
    this->currentAvailableActions = this->maximumAvailableActions;
}

void Unit::decreaseAvailableActions() {
    FMAW::printf("BEFORE %d of %d actions available, %d",
                 this->currentAvailableActions, this->maximumAvailableActions,
                 this->movementCapacity);
    this->currentAvailableActions--;
    if (this->currentAvailableActions < 0) {
        this->currentAvailableActions = 0;
    }
    FMAW::printf("AFTER %d of %d actions available, %d",
                 this->currentAvailableActions, this->maximumAvailableActions,
                 this->movementCapacity);
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