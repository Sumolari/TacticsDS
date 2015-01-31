#ifndef FMAW_SPRITE_H
#define FMAW_SPRITE_H

#include "./geometry.h"

namespace FMAW {

//------------------------------------------------------------------------------
// Common sprite constants and variables.
//------------------------------------------------------------------------------

// Access to sprites' memory, in an array-like way.
#define sprites       (reinterpret_cast<FMAW::SpriteEntry*>OAM)

#define TOTAL_SPRITES 128  // Total amount of sprites that can be rendered.

// Low-level data structure to work with NDS libraries.
typedef struct t_spriteEntry {
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 affine_data;
} SpriteEntry;

// Type that defines the ID of a sprite.
typedef uint8 sprite_id;

// Type defining the different size modes available.
typedef enum t_spriteSizeMode {
    square8x8,
    square16x16,
    square32x32,
    square64x64,
    wide16x8,
    wide32x8,
    wide32x16,
    wide64x32,
    tall8x16,
    tall8x32,
    tall16x32,
    tall32x64,
    unknown
} SpriteSizeMode;

//------------------------------------------------------------------------------
// Common sprite helpers.
//------------------------------------------------------------------------------

/**
 * Clears all the sprites.
 */
void clearAllSprites(void);

/**
 * Disables given sprite (it won't be rendered and no CPU cycles will be wasted
 * on it).
 */
void disableSprite( sprite_id id );

//------------------------------------------------------------------------------
// Sprite class.
//------------------------------------------------------------------------------

class Sprite {
private:
    // Actual struct holding sprite internal data.
    t_spriteEntry entry;


public:
    // ID of this sprite.
    uint8 id;
    // Next empty sprite.
    static uint8 nextEmptySprite;

    /**
     * Default constructor takes a valid ID automatically.
     */
    Sprite() : id( nextEmptySprite++ ) {};

    //--------------------------------------------------------------------------
    // Position.
    //--------------------------------------------------------------------------

    /**
     * Sets x position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     *
     * @see FMAW::setPosition
     *
     * @param  x New value for x-offset.
     * @return   Whether desired chaged was applied or not.
     */
    bool setXPosition( int x );

    /**
     * Sets y position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     *
     * @see FMAW::setPosition
     *
     * @param  y New value for y-offset.
     * @return   Whether desired chaged was applied or not.
     */
    bool setYPosition( int y );

    /**
     * Sets x and y position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     * Only applies change if BOTH changes are possible.
     *
     * @see FMAW::setXPosition
     * @see FMAW::setYPosition
     *
     * @param  x New value for x-offset.
     * @param  y New value for y-offset.
     * @return   Whether BOTH changes where applied or not.
     */
    bool setPosition( int x, int y );

    /**
     * Sets x and y position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     * Only applies change if BOTH changes are possible.
     *
     * @see FMAW::setPosition
     *
     * @param  point New position.
     * @return       Whether BOTH changes where applied or not.
     */
    bool setPosition( Point point );

    /**
     * Returns current x-offset of this sprite.
     * @return x-offset of this sprite.
     */
    int getXPosition();

    /**
     * Returns current y-offset of this sprite.
     * @return y-offset of this sprite.
     */
    int getYPosition();

    /**
     * Returns current position of this sprite.
     * @return Position of this sprite.
     */
    Point getPosition();

    //--------------------------------------------------------------------------
    // Tile & palette settings.
    //--------------------------------------------------------------------------

    /**
     * Sets this sprite's tile to given one.
     * @param tileIndex  Index of tile to use.
     * @return           Whether tile can be used or not.
     */
    bool setTile( uint16 tileIndex );

    /**
     * Sets this sprite's palette to given one.
     * @param  paletteIndex Index of palette to use.
     * @return              Whether palette can be used or not.
     */
    bool setPalette( uint8 paletteIndex );

    //--------------------------------------------------------------------------
    // Other settings.
    //--------------------------------------------------------------------------

    // _TODO: Add method to enable this sprite.

    /**
     * Disables this sprite (it won't be rendered and no CPU cycles will be
     * wasted on it).
     */
    void disable();

    /**
     * Sets this sprite's size mode to given mode.
     * @param newMode New Sprite Mode for this sprite.
     * @return        Whether newMode can be applied or not.
     */
    bool setSizeMode( SpriteSizeMode newMode );

    /**
     * Returns this sprite's size mode.
     * @return This sprite's size mode.
     */
    SpriteSizeMode getSizeMode();

};


}

#endif