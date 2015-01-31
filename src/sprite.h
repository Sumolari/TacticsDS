#ifndef FMAW_SPRITE_H
#define FMAW_SPRITE_H

namespace FMAW {

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

/**
 * Clears all the sprites.
 */
void clearAllSprites(void);

/**
 * Disables given sprite (it won't be rendered and no CPU cycles will be wasted
 * on it).
 */
void disableSprite( sprite_id id );

}

#endif