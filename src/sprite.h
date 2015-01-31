#ifndef FMAW_SPRITE_H
#define FMAW_SPRITE_H

#include "./geometry.h"

namespace FMAW {

//------------------------------------------------------------------------------
// Common sprite constants and variables.
//------------------------------------------------------------------------------

// Access to sprites' memory, in an array-like way.
#define sprites       (reinterpret_cast<FMAW::spriteEntry*>OAM)

#define TOTAL_SPRITES 128  // Total amount of sprites that can be rendered.

// Low-level data structure to work with NDS libraries.
typedef struct t_spriteEntry {
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 affine_data;
} spriteEntry;

typedef uint8 sprite_id;

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

};


}

#endif