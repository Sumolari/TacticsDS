#ifndef CURSOR_H
#define CURSOR_H

#include "./FMAW.h"

class Cursor : public FMAW::Character {

  private:
    /**
     * Tile of the squared cursor.
     */
    FMAW::Tile tileSquare;

    /**
     * Tile of the arrow cursor.
     */
    FMAW::Tile tileArrow;

    /**
     * Tile of the cross cursor.
     */
    FMAW::Tile tileCross;

  public:
    /**
     * Creates a new cursor.
     */
    Cursor();

    /**
     * Initializes tiles for the cursor.
     */
    void init();

    /**
     * Sets the cursor to be an arrow.
     */
    void setArrow();

    /**
     * Sets the cursor to be an square.
     */
    void setSquare();

    /**
     * Sets the cursor to be a cross.
     */
    void setCross();

};

#endif