#ifndef FMAW_BACKGROUND_H
#define FMAW_BACKGROUND_H

namespace FMAW {

#define TOTAL_BACKGROUNDS 4  // Total amount of backgrounds available.

// Type defining the different priorities of backgrounds.
typedef enum t_backgroundPriority {
    bpHIGHEST = 0xFFFC,
    bpHIGH    = 0xFFFD,
    bpLOW     = 0xFFFE,
    bpLOWEST  = 0xFFFF
} BackgroundPriority;

// Type defining the different sizes of backgrounds.
typedef enum t_backgroundSize {
    size32x32 = 0x3FFF,
    size64x32 = 0x7FFF,
    size32x64 = 0xBFFF,
    size64x64 = 0xFFFF
} BackgroundSize;

// Type that defines the ID of a background.
typedef uint8 background_id;

// Type that defines the ID of a background tile.
typedef uint16 background_tile_id;

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

    /**
     * Returns tilemap address of this background.
     * @return This background's tilemap address.
     */
    vu16 *tilemap();

    /**
     * Returns the register used to store this background's info.
     * @return Register used to store this background's info.
     */
    vu16 *reg();


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

    /**
     * Returns whether display area overflow bit os this background is disabled
     * or not.
     * @return False if display area overflow bit of this background is enabled.
     */
    bool displayAreaOverflowDisabled();

    //--------------------------------------------------------------------------
    // Tile & palette settings.
    //--------------------------------------------------------------------------

    /**
    * Sets tile index of given tile in this background to given one.
    * @param  tile_id    ID of the affected tile.
    * @param  tileIndex  Index of tile to use.
    * @return            Whether change could be applied or not.
    */
    bool setTile( background_tile_id tile_id, uint16 tileIndex );

    /**
     * Returns tile index of given tile in this background.
     * @param  tile_id ID of the affected tile.
     * @return         Tile index of given tile in this background.
     */
    uint16 getTile( background_tile_id tile_id );

    /**
     * Sets palette of given tile in this background's to given palette.
     * @param  tile_id      ID of the affected tile.
     * @param  paletteIndex Index of palette to use.
     * @return              Whether change could be applied or not.
     */
    bool setPalette( background_tile_id tile_id, uint8 paletteIndex );

    /**
     * Returns palette index of given tile in this background.
     * @param  tile_id ID of the affected tile.
     * @return         Palette index of given tile in this background.
     */
    uint8 getPalette( background_tile_id tile_id );

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
     * Enables horizontal flip for given tile in this background.
     * @param  tile_id ID of the affected tile.
     */
    void enableHorizontalFlip( background_tile_id tile_id );

    /**
     * Disables horizontal flip for given tile in this background.
     * @param  tile_id ID of the affected tile.
     */
    void disableHorizontalFlip( background_tile_id tile_id );

    /**
     * Returns whether horizontal flip is enabled for given tile in this
     * background or not.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether horizontal flip is enabled for given tile in this
     *                 background or not.
     */
    bool horizontalFlipIsEnabled( background_tile_id tile_id );

    /**
     * Returns whether horizontal flip is disabled for given tile in this
     * background or not.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether horizontal flip is disabled for given tile in
     *                 this background or not.
     */
    bool horizontalFlipIsDisabled( background_tile_id tile_id );

    /**
     * Enables vertical flip for given tile in this background.
     * @param  tile_id ID of the affected tile.
     */
    void enableVerticalFlip( background_tile_id tile_id );

    /**
     * Disables vertical flip for given tile in this background.
     * @param  tile_id ID of the affected tile.
     */
    void disableVerticalFlip( background_tile_id tile_id );

    /**
     * Returns whether vertical flip is enabled for given tile in this
     * background.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether vertical flip is enabled for given tile in this
     *                 background or not.
     */
    bool verticalFlipIsEnabled( background_tile_id tile_id );

    /**
     * Returns whether vertical flip is disabled for given tile in this
     * background or not.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether vertical flip is disabled for given tile in this
     *                 background or not.
     */
    bool verticalFlipIsDisabled( background_tile_id tile_id );

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

    /**
    * Resets all tiles of this background.
    */
    void clearAllTiles();

};

}

#endif