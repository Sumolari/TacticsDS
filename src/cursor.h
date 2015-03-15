#ifndef CURSOR_H
#define CURSOR_H

#include "./FMAW.h"

class Cursor : public FMAW::Character {

  private:
    /**
     * TileAttributes of the squared cursor.
     */
    FMAW::TileAttributes tileSquare;

    /**
     * TileAttributes of the arrow cursor.
     */
    FMAW::TileAttributes tileArrow;

    /**
     * TileAttributes of the cross cursor.
     */
    FMAW::TileAttributes tileCross;

    /**
     * Actual tile used by the cross cursor.
     */
    FMAW::Tile tile;

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