#ifndef FMAW_BACKGROUND_H
#define FMAW_BACKGROUND_H

namespace FMAW {

#define TOTAL_BACKGROUNDS 4  // Total amount of backgrounds available.

// Type defining the different priorities of backgrounds.
typedef enum t_backgroundPriority {
    bpHIGHEST = 0x0,
    bpHIGH    = 0x1,
    bpLOW     = 0x2,
    bpLOWEST  = 0x3
} BackgroundPriority;

// Type defining the different sizes of backgrounds.
typedef enum t_backgroundSize {
    size32x32 = 0x0,
    size64x32 = 0x1,
    size32x64 = 0x2,
    size64x64 = 0x3
} BackgroundSize;

// Type that defines the ID of a background.
typedef uint8 background_id;

class Background {

public:
    // ID of this background.
    background_id id;
    // Next empty background.
    static background_id nextEmptyBackground;

    /**
    * Default constructor takes a valid ID automatically.
    */
    Background() : id( nextEmptyBackground++ ) {
        this->clear();
    };

    /**
     * Constructor for Background with given ID. Background should have been
     * previously created otherwise results are not defined.
     */
    Background( background_id id ) : id(id) {};

    //--------------------------------------------------------------------------
    // Position.
    //--------------------------------------------------------------------------

    /**
     * Sets this background's character base block if given value is valid.
     * @param  characterBaseBlock Character block for this background (0..15)
     * @return                    Whether change could be applied or not.
     */
    bool setCharacterBaseBlock( uint8 characterBaseBlock );

    /**
     * Returns this background's character base block.
     * @return Character base block of this background.
     */
    uint8 getCharacterBaseBlock();

    /**
     * Sets this background's screen base block if given value is valid.
     * @param  newScreenBaseBlock Screen base block for this background (0..31)
     * @return                    Whether change chould be applied or not.
     */
    bool setScreenBaseBlock( uint8 newScreenBaseBlock );

    /**
     * Returns this background's screen base block.
     * @return Screen base block of this background.
     */
    uint8 getScreenBaseBlock();

    /**
     * Enables display area overflow bit for this background.
     */
    void enableDisplayAreaOverflow();

    /**
     * Disables display area overflow bit for this background.
     */
    void disableDisplayAreaOverflow();

    /**
     * Returns value of display area overflow bit of this background.
     * @return True if display area overflow bit of this background is enabled.
     */
    bool displayAreaOverflowEnabled();

    //--------------------------------------------------------------------------
    // Tile & palette settings.
    //--------------------------------------------------------------------------

    /**
    * Sets this background's tile to given one.
    * @param tileIndex  Index of tile to use.
    * @return           Whether tile can be used or not.
    */
    bool setTile( uint16 tileIndex );

    /**
     * Returns this background's tile index.
     * @return Tile of this background index.
     */
    uint16 getTile();

    /**
     * Sets this background's palette to given one.
     * @param  paletteIndex Index of palette to use.
     * @return              Whether palette can be used or not.
     */
    bool setPalette( uint8 paletteIndex );

    /**
     * Returns this background's palette index.
     * @return Palette index of this background.
     */
    uint8 getPalette();

    //--------------------------------------------------------------------------
    // Mosaic & color settings.
    //--------------------------------------------------------------------------

    /**
     * Enables mosaic mode for this background.
     */
    void enableMosaic();

    /**
     * Disables mosaic mode for this background.
     */
    void disableMosaic();

    /**
     * Returns whether mosaic mode is enabled for this background.
     * @return Whether mosaic mode is enabled for this background.
     */
    bool mosaicIsEnabled();

    /**
     * Returns whether mosaic mode is disabled for this background.
     * @return Whether mosaic mode is disabled for this background.
     */
    bool mosaicIsDisabled();

    /**
     * Enables 16 bit textures for this background.
     */
    void use16BitColors();

    /**
     * Enables 256 bit textures for this background.
     */
    void use256BitColors();

    /**
     * Returns whether this background is using 16 bit textures or not.
     * @return Whether this background is using 16 bit textures or not.
     */
    bool isUsing16BitColors();

    /**
     * Returns whether this background is using 256 bit textures or not.
     * @return Whether this background is using 256 bit textures or not.
     */
    bool isUsing256BitColors();

    //--------------------------------------------------------------------------
    // Shape & size settings.
    //--------------------------------------------------------------------------

    /**
     * Sets size of this background.
     * @param  newSize New size for this background.
     */
    void setSize( BackgroundSize newSize );

    /**
     * Returns current size of this background.
     * @return Size of this background.
     */
    BackgroundSize getSize();

    //--------------------------------------------------------------------------
    // Flip settings.
    //--------------------------------------------------------------------------

    /**
     * Enables horizontal flip for this background.
     */
    void enableHorizontalFlip();

    /**
     * Disables horizontal flip for this background.
     */
    void disableHorizontalFlip();

    /**
     * Returns whether horizontal flip is enabled for this background or not.
     * @return Whether horizontal flip is enabled for this background or not.
     */
    bool horizontalFlipIsEnabled();

    /**
     * Returns whether horizontal flip is disabled for this background or not.
     * @return Whether horizontal flip is disabled for this background or not.
     */
    bool horizontalFlipIsDisabled();

    /**
     * Enables vertical flip for this background.
     */
    void enableVerticalFlip();

    /**
     * Disables vertical flip for this background.
     */
    void disableVerticalFlip();

    /**
     * Returns whether vertical flip is enabled for this background or not.
     * @return Whether vertical flip is enabled for this background or not.
     */
    bool verticalFlipIsEnabled();

    /**
     * Returns whether vertical flip is disabled for this background or not.
     * @return Whether vertical flip is disabled for this background or not.
     */
    bool verticalFlipIsDisabled();

    //--------------------------------------------------------------------------
    // Priority settings.
    //--------------------------------------------------------------------------

    /**
     * Sets priority of this background.
     * @param priority New priority of this background.
     */
    void setPriority( BackgroundPriority priority );

    /**
     * Returns the priority of this background.
     * @return This background's priority.
     */
    BackgroundPriority getPriority();

    //--------------------------------------------------------------------------
    // Other settings.
    //--------------------------------------------------------------------------

    /**
     * Resets VRAM of this background to 0.
     */
    void clear();

};

}

#endif