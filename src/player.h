#ifndef PLAYER_H
#define PLAYER_H

typedef int PlayerID;

class Player {

  protected:
    // ID of this player.
    PlayerID ID;

  public:
    /**
     * Creates a new Player, taking an automatic, valid, ID.
     */
    Player();

    /**
     * Creates a new Player, given his ID.
     */
    explicit Player(PlayerID);

    /**
     * Returns the ID of this player.
     * @return ID of this player.
     */
    PlayerID getID();

    /**
     * Tells this player that he can start playing.
     */
    virtual void startTurn();

    /**
     * Prints information about this player.
     */
    virtual void print();

    virtual ~Player() = default;
};

#endif