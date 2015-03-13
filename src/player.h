#ifndef PLAYER_H
#define PLAYER_H

typedef int PlayerID;

class Player {

  private:
    // ID of this player.
    PlayerID ID;

  public:
    /**
     * Creates a new Player, taking an automatic, valid, ID.
     */
    Player();

    /**
     * Returns the ID of this player.
     * @return ID of this player.
     */
    PlayerID getID();

    /**
     * Tells this player that he can start playing.
     */
    void startTurn();

};

#endif