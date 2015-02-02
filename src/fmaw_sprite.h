#ifndef FMAW_SPRITE_H
#define FMAW_SPRITE_H

#include "./fmaw_types.h"
#include "./fmaw_geometry.h"

namespace FMAW {

//------------------------------------------------------------------------------
// Common sprite constants and variables.
//------------------------------------------------------------------------------

// Low-level data structure to work with NDS libraries.
typedef struct t_spriteEntry {
    uint16 attr0;
    uint16 attr1;
    uint16 attr2;
    uint16 affine_data;
} SpriteEntry;

// Access to sprites' memory, in an array-like way.
#define sprites       (reinterpret_cast<FMAW::SpriteEntry*>OAM)

#define TOTAL_SPRITES 128  // Total amount of sprites that can be rendered.

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

// Type defining the different object modes available.
typedef enum t_spriteObjectMode {
    normal             = 0xF3FF,
    alpha_first_target = 0xF7FF,
    add_to_window      = 0xFBFF,
    bitmap             = 0xFFFF
} SpriteObjectMode;

// Type defining the different priorities of backgrounds.
typedef enum t_spritePriority {
    spHIGHEST = 0xF3FF,
    spHIGH    = 0xF7FF,
    spLOW     = 0xFBFF,
    spLOWEST  = 0xFFFF
} SpritePriority;

//------------------------------------------------------------------------------
// Common sprite helpers.
//------------------------------------------------------------------------------

/**
 * Clears all sprites in memory.
 */
void clearAllSprites();

//------------------------------------------------------------------------------
// Sprite class.
//------------------------------------------------------------------------------

class Sprite {
public:
    // ID of this sprite.
    sprite_id id;
    // Next empty sprite.
    static sprite_id nextEmptySprite;

    /**
     * Default constructor takes a valid ID automatically.
     */
    Sprite() : id(nextEmptySprite++) {
        FMAW::printf("MY ID IS %d", this->id);
        this->clear();
    };

    /**
     * Constructor for Sprite with given ID. Sprite should have been previously
     * created otherwise results are not defined.
     */
    Sprite(sprite_id id) : id(id) {};

    //--------------------------------------------------------------------------
    // Position.
    //--------------------------------------------------------------------------

    /**
     * Sets x position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     *
     * @see Sprite::setPosition()
     *
     * @param  x New value for x-offset.
     * @return   Whether desired chaged was applied or not.
     */
    bool setXPosition(int x);

    /**
     * Sets y position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     *
     * @see Sprite::setPosition()
     *
     * @param  y New value for y-offset.
     * @return   Whether desired chaged was applied or not.
     */
    bool setYPosition(int y);

    /**
     * Sets x and y position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     * Only applies change if BOTH changes are possible.
     *
     * @see Sprite::setXPosition()
     * @see Sprite::setYPosition()
     *
     * @param  x New value for x-offset.
     * @param  y New value for y-offset.
     * @return   Whether BOTH changes where applied or not.
     */
    bool setPosition(int x, int y);

    /**
     * Sets x and y position of this sprite.
     * Handles negative values and overflows by not applying the change and
     * returning false.
     * Only applies change if BOTH changes are possible.
     *
     * @see Sprite::setPosition()
     *
     * @param  point New position.
     * @return       Whether BOTH changes where applied or not.
     */
    bool setPosition(Point point);

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
    bool setTile(uint16 tileIndex);

    /**
     * Returns this sprite's tile index.
     * @return Tile of this sprite index.
     */
    uint16 getTile();

    /**
     * Sets this sprite's palette to given one.
     * @param  paletteIndex Index of palette to use.
     * @return              Whether palette can be used or not.
     */
    bool setPalette(uint8 paletteIndex);

    /**
     * Returns this sprite's palette index.
     * @return Palette index of this sprite.
     */
    uint8 getPalette();

    //--------------------------------------------------------------------------
    // Rotation & scale settings.
    //--------------------------------------------------------------------------

    /**
     * Enables rotation and scale of this sprite.
     */
    void enableRotationAndScale();

    /**
     * Disables rotation and scale of this sprite.
     * Double-size will be disabled, too.
     */
    void disableRotationAndScale();

    /**
     * Returns whether rotation and scaling are enabled in this sprite or not.
     * @return Whether rotation and scaling are enabled in this sprite or not.
     */
    bool rotationAndScaleAreEnabled();

    /**
     * Returns whether rotation and scaling are disabled in this sprite or not.
     * @return Whether rotation and scaling are disabled in this sprite or not.
     */
    bool rotationAndScaleAreDisabled();

    /**
     * Enables double size of this sprite.
     * Will enable also rotation and scaling.
     */
    void enableDoubleSize();

    /**
     * Disables double size of this sprite.
     */
    void disableDoubleSize();

    /**
     * Returns whether double size is enabled or not.
     * @return Whether double size is enabled or not.
     */
    bool doubleSizeEnabled();

    /**
     * Returns whether double size is enabled or not.
     * @return Whether double size is enabled or not.
     */
    bool doubleSizeDisabled();

    //--------------------------------------------------------------------------
    // Object mode settings.
    //--------------------------------------------------------------------------

    /**
     * Sets this sprite's object mode to given one.
     * @param newMode This sprite's object mode.
     */
    void setObjectMode(SpriteObjectMode newMode);

    /**
     * Returns this sprite's object mode.
     * @return Object mode of this sprite.
     */
    SpriteObjectMode getObjectMode();

    //--------------------------------------------------------------------------
    // Mosaic & color settings.
    //--------------------------------------------------------------------------

    /**
     * Enables mosaic mode for this sprite.
     */
    void enableMosaic();

    /**
     * Disables mosaic mode for this sprite.
     */
    void disableMosaic();

    /**
     * Returns whether mosaic mode is enabled for this sprite.
     * @return Whether mosaic mode is enabled for this sprite.
     */
    bool mosaicIsEnabled();

    /**
     * Returns whether mosaic mode is disabled for this sprite.
     * @return Whether mosaic mode is disabled for this sprite.
     */
    bool mosaicIsDisabled();

    /**
     * Enables 16 bit textures for this sprite.
     */
    void use16BitColors();

    /**
     * Enables 256 bit textures for this sprite.
     */
    void use256BitColors();

    /**
     * Returns whether this sprite is using 16 bit textures or not.
     * @return Whether this sprite is using 16 bit textures or not.
     */
    bool isUsing16BitColors();

    /**
     * Returns whether this sprite is using 256 bit textures or not.
     * @return Whether this sprite is using 256 bit textures or not.
     */
    bool isUsing256BitColors();

    //--------------------------------------------------------------------------
    // Shape & size settings.
    //--------------------------------------------------------------------------

    /**
     * Sets this sprite's size mode to given mode.
     * @param newMode New Sprite Mode for this sprite.
     * @return        Whether newMode can be applied or not.
     */
    bool setSizeMode(SpriteSizeMode newMode);

    /**
     * Returns this sprite's size mode.
     * @return This sprite's size mode.
     */
    SpriteSizeMode getSizeMode();

    //--------------------------------------------------------------------------
    // Flip settings.
    //--------------------------------------------------------------------------

    /**
     * Enables horizontal flip for this sprite.
     * This will disable rotation/scale for this sprite.
     */
    void enableHorizontalFlip();

    /**
     * Disables horizontal flip for this sprite.
     * This will disable rotation/scale for this sprite.
     */
    void disableHorizontalFlip();

    /**
     * Returns whether horizontal flip is enabled for this sprite or not.
     * If rotation/scaling is disabled it'll return false.
     * @return Whether horizontal flip is enabled for this sprite or not.
     */
    bool horizontalFlipIsEnabled();

    /**
     * Returns whether horizontal flip is disabled for this sprite or not.
     * If rotation/scaling is disabled it'll return false.
     * THIS IS NOT EQUIVALENT TO !horizontalFlipIsEnabled() !!
     * @return Whether horizontal flip is disabled for this sprite or not.
     */
    bool horizontalFlipIsDisabled();

    /**
     * Enables vertical flip for this sprite.
     * This will disable rotation/scale for this sprite.
     */
    void enableVerticalFlip();

    /**
     * Disables vertical flip for this sprite.
     * This will disable rotation/scale for this sprite.
     */
    void disableVerticalFlip();

    /**
     * Returns whether vertical flip is enabled for this sprite or not.
     * If rotation/scaling is disabled it'll return false.
     * @return Whether vertical flip is enabled for this sprite or not.
     */
    bool verticalFlipIsEnabled();

    /**
     * Returns whether vertical flip is disabled for this sprite or not.
     * If rotation/scaling is disabled it'll return false.
     * THIS IS NOT EQUIVALENT TO !verticalFlipIsEnabled() !!
     * @return Whether vertical flip is disabled for this sprite or not.
     */
    bool verticalFlipIsDisabled();

    //--------------------------------------------------------------------------
    // Transform settings.
    //--------------------------------------------------------------------------

    /**
     * Applies given transform to this sprite.
     * It will enable scaling and rotation for this sprite.
     * @param transform Transform to apply.
     */
    void applyTransform(Transform transform);

    //--------------------------------------------------------------------------
    // Priority settings.
    //--------------------------------------------------------------------------

    /**
     * Sets priority of this sprite.
     * @param priority New priority of this sprite.
     */
    void setPriority(SpritePriority priority);

    /**
     * Returns the priority of this sprite.
     * @return This sprite's priority.
     */
    SpritePriority getPriority();

    //--------------------------------------------------------------------------
    // Other settings.
    //--------------------------------------------------------------------------

    /**
     * Resets VRAM of this sprite to 0.
     */
    void clear();

    /**
     * Disables this sprite (it won't be rendered and no CPU cycles will be
     * wasted on it).
     */
    void disable();

    /**
     * Enables this sprite (it might be rendered but it will consume CPU cycles
     * for sure).
     */
    void enable();

    /**
     * Prints a description of this Sprite in debug console.
     */
    void print();

};

}

#endif