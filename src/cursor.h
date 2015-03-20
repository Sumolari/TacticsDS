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
     * TileAttributes of the sword cursor.
     */
    FMAW::TileAttributes tileSword;

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
     * Shows cursor.
     */
    void enable();

    /**
     * Hides cursor.
     */
    void disable();

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
    
    /**
     * Sets the cursor to be a sword.
     */
    void setSword();

};

#endif
