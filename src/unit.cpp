// Copyright 2015 FMAW

#include "./unit.h"

#include "./FMAW.h"

#include "./constants.h"
#include "./warrior.h"
#include "./knight.h"
#include "./sniper.h"

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
        case UNIT_TYPE_KNIGHT:
            return new Knight(ownerID);
        case UNIT_TYPE_SNIPER:
            return new Sniper(ownerID);
        default:
            return new Unit(ownerID);
    }
}

void Unit::init() {}

void Unit::update() {}

void Unit::update_freq() {}

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

int Unit::getSightDistance() {
    return this->sightDistance;
}

int Unit::getMaximumHealth() {
    return this->maximumHealth;
}
int Unit::getCurrentHealth() {
    return this->currentHealth;
}

void Unit::setCurrentHealth(int h) {
    this->currentHealth = h;
}

int Unit::getMinimumAttackRange() {
    return this->minimumAttackRange;
}
int Unit::getMaximumAttackRange() {
    return this->maximumAttackRange;
}

int Unit::force() {
    return this->attackPower;
}

bool Unit::attackUnit(Unit *u) {
    u->setCurrentHealth(u->getCurrentHealth() - this->force());

    if (u->getCurrentHealth() <= 0) {
        delete(u);
        return true;
    }

    u->update_freq();

    return false;
}

PlayerID Unit::getOwner() {
    return this->ownerID;
}

PlayerID Unit::setOwner(PlayerID owner) {
    PlayerID prev = this->ownerID;
    this->ownerID = owner;
    return prev;
}
