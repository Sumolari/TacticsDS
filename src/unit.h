#ifndef UNIT_H
#define UNIT_H

#include "./FMAW.h"

#include "./player.h"

class Unit : public FMAW::Character {
  protected:
    /**
     * ID of player who owns this unit.
     */
    PlayerID ownerID;

    /**
     * Type of this unit.
     */
    int unitType;

    virtual void init();
  public:
    /**
     * Amount of movement points that this Unit has available.
     */
    int movementCapacity;

    /**
     * Maximum amount of available actions this Unit has.
     */
    int maximumAvailableActions;

    /**
     * Amount of remaining available actions this Unit has.
     */
    int currentAvailableActions;

	/**
	 * Maximum amount of health this Unit has.
	 */
	int maximumHealth;
	/**
	 * Amount of health this Unit currently has.
	 */
	int currentHealth;
	
	/**
	 * Minimum range from which this Unit can attack.
	 */
	int minimumAttackRange;
	/**
	 * Maximum range from which this Unit can attack.
	 */
	int maximumAttackRange;

	/**
	 * Attack power of this Unit.
	 */
	int attackPower;

    /**
     * Creates a new unit using a new sprite.
     */
    explicit Unit(PlayerID ownerID);

    /**
     * Creates a new unit given its sprite.
     */
    explicit Unit(FMAW::Sprite sprite);

    /**
     * Creates a new unit given its sprite and owner.
     */
    explicit Unit(FMAW::Sprite sprite, PlayerID ownerID);

    /**
     * Factory method to get units knowing their type.
     * @param  unitType Type of the unit.
     * @param  ownerID  Owner of the unit.
     * @return          New unit of given type.
     */
    static Unit *UnitWithType(int unitType, PlayerID ownerID);

    virtual void update();
    
    virtual void update_freq();

    /**
     * Returns the internal type identifier for this kind of Unit.
     * @return Integer representing the type of this unit.
     */
    int getUnitType();

    /**
     * Returns the movement capacity of this Unit.
     * @return Movement capacity of this Unit.
     */
    int getMovementCapacity();

	/**
     * Returns the maximum health of this Unit.
     * @return Maximum health of this Unit.
     */
    int getMaximumHealth();
    /**
     * Returns the current health of this Unit.
     * @return Current health of this Unit.
     */
    int getCurrentHealth();

    /**
     * Sets the current health of this Unit to the given value.
     * @param h  New value for the current health of this Unit.
     */
    void setCurrentHealth(int h);

    /**
     * Returns the minimum attack range of this Unit.
     * @return Minimum attack range of this Unit.
     */
    int getMinimumAttackRange();
    /**
     * Returns the maximum attack range of this Unit.
     * @return Maximum attack range of this Unit.
     */
    int getMaximumAttackRange();
    
    /**
     * Returns the attack power of this Unit.
     * @return Attack power of this Unit.
     */
    int force();
    
    /**
     * Returns true if the attacked unit is alive afterwards.
     * False otherwise.
     * @param u  The unit to attack.
     * @return   Attacked unit aliveness.
     */
    bool attackUnit(Unit *u);

    /**
     * Resets the internal counter of available actions.
     */
    void resetAvailableActions();

    /**
     * Decreases the internal counter of available actions.
     */
    void decreaseAvailableActions();

    /**
     * Returns whether this Unit has at least one available action or not.
     * @return Whether this Unit has at least oen available action or not.
     */
    bool hasAvailableActions();

    /**
     * Returns the ID of the owner of this unit.
     * @return ID of the owner of this unit.
     */
    PlayerID getOwner();

    /**
     * Sets owner of this unit.
     * @param owner New owner of this unit.
     * @return      Previous owner of this unit.
     */
    PlayerID setOwner(PlayerID owner);

    virtual ~Unit() = default;
};

#endif
