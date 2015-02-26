#ifndef FMAW_BACKGROUND_H
#define FMAW_BACKGROUND_H

#include "./fmaw_types.h"
#include "./fmaw_tile.h"

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

typedef enum t_alphaBlendingMode {
    babmDisable,
    babmAlphaBlending,
    babmFadeImageBright,
    babmFadeImageDark
} BackgroundAlphaBlendingMode;

void setBackgroundColor(unsigned int color);

class Background {

  private:
    // Register holding this background data.
    vu16 *reg;
    // Register holding this background's vertical offset.
    vu16 *vOffset;
    // Register holding this background's horizontal offset.
    vu16 *hOffset;

    /**
     * Sets internal register attrbute to proper address based on ID.
     */
    void selectRegister();

  public:
    // Tiles register array.
    u16 *tiles;
    // ID of this background.
    background_id id;
    // Next empty background.
    static background_id nextEmptyBackground;

    /**
     * Default constructor takes a valid ID automatically.
     */
    Background();

    /**
     * Constructor for Background with given ID. Background should have been
     * previously created otherwise results are not defined.
     */
    Background(background_id id);

    //--------------------------------------------------------------------------
    // Position.
    //--------------------------------------------------------------------------

    /**
     * Sets this background's character base block if given value is valid.
     * @param  characterBaseBlock Character block for this background (0..15)
     * @return                    Whether change could be applied or not.
     */
    bool setCharacterBaseBlock(uint8 characterBaseBlock);

    /**
     * Returns this background's character base block.
     * @return Character base block of this background.
     */
    uint8 getCharacterBaseBlock();

    /**
     * Sets this background's screen base block if given value is valid.
     * Automatically changes internal tiles pointer to work with proper tiles.
     *
     * @param  newScreenBaseBlock Screen base block for this background (0..31)
     * @return                    Whether change chould be applied or not.
     */
    bool setScreenBaseBlock(uint8 newScreenBaseBlock);

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

    /**
     * Sets vertical offset of this background to given value.
     * @param offset New vertical offset for this background.
     */
    void setVerticalOffset(uint8 offset);

    /**
     * Returns vertical offset of this background.
     * @return This background's vertical offset.
     */
    uint8 getVerticalOffset();

    /**
     * Sets horizontal offset of this background to given value.
     * @param offset New horizontal offset for this background.
     */
    void setHorizontalOffset(uint8 offset);

    /**
     * Returns horizontal offset of this background.
     * @return This background's horizontal offset.
     */
    uint8 getHorizontalOffset();

    //--------------------------------------------------------------------------
    // Tile & palette settings.
    //--------------------------------------------------------------------------

    /**
     * Sets tile of given tile in this background to given one.
     * @param  tile_id    ID of the affected tile.
     * @param  tile       Tile to use.
     * @return            Whether change could be applied or not.
     */
    bool setTile(background_tile_id tile_id, Tile tile);

    /**
     * Sets tile index of given tile in this background to given one.
     * @param  tile_id    ID of the affected tile.
     * @param  tileIndex  Index of tile to use.
     * @return            Whether change could be applied or not.
     */
    bool setTile(background_tile_id tile_id, uint16 tileIndex);

    /**
     * Returns tile index of given tile in this background.
     * @param  tile_id ID of the affected tile.
     * @return         Tile index of given tile in this background.
     */
    uint16 getTile(background_tile_id tile_id);

    /**
     * Sets palette of given tile in this background's to given palette.
     * @param  tile_id      ID of the affected tile.
     * @param  paletteIndex Index of palette to use.
     * @return              Whether change could be applied or not.
     */
    bool setPalette(background_tile_id tile_id, uint8 paletteIndex);

    /**
     * Returns palette index of given tile in this background.
     * @param  tile_id ID of the affected tile.
     * @return         Palette index of given tile in this background.
     */
    uint8 getPalette(background_tile_id tile_id);

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
    void setSize(BackgroundSize newSize);

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
    void enableHorizontalFlip(background_tile_id tile_id);

    /**
     * Disables horizontal flip for given tile in this background.
     * @param  tile_id ID of the affected tile.
     */
    void disableHorizontalFlip(background_tile_id tile_id);

    /**
     * Returns whether horizontal flip is enabled for given tile in this
     * background or not.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether horizontal flip is enabled for given tile in this
     *                 background or not.
     */
    bool horizontalFlipIsEnabled(background_tile_id tile_id);

    /**
     * Returns whether horizontal flip is disabled for given tile in this
     * background or not.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether horizontal flip is disabled for given tile in
     *                 this background or not.
     */
    bool horizontalFlipIsDisabled(background_tile_id tile_id);

    /**
     * Enables vertical flip for given tile in this background.
     * @param  tile_id ID of the affected tile.
     */
    void enableVerticalFlip(background_tile_id tile_id);

    /**
     * Disables vertical flip for given tile in this background.
     * @param  tile_id ID of the affected tile.
     */
    void disableVerticalFlip(background_tile_id tile_id);

    /**
     * Returns whether vertical flip is enabled for given tile in this
     * background.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether vertical flip is enabled for given tile in this
     *                 background or not.
     */
    bool verticalFlipIsEnabled(background_tile_id tile_id);

    /**
     * Returns whether vertical flip is disabled for given tile in this
     * background or not.
     *
     * @param  tile_id ID of the affected tile.
     * @return         Whether vertical flip is disabled for given tile in this
     *                 background or not.
     */
    bool verticalFlipIsDisabled(background_tile_id tile_id);

    //--------------------------------------------------------------------------
    // Priority settings.
    //--------------------------------------------------------------------------

    /**
     * Sets priority of this background.
     * @param priority New priority of this background.
     */
    void setPriority(BackgroundPriority priority);

    /**
     * Returns the priority of this background.
     * @return This background's priority.
     */
    BackgroundPriority getPriority();

    //--------------------------------------------------------------------------
    // Alpha settings.
    //--------------------------------------------------------------------------

    /**
     * Sets this background as source background for alpha blending.
     * If this background was destination background for alpha blending it
     * won't be anymore.
     */
    void useAsAlphaBlendingSrc();

    /**
     * Sets this background as destination background for alpha blending.
     * If this background was source background for alpha blending it won't be
     * anymore.
     */
    void useAsAlphaBlendingDst();

    /**
     * Use backdrop as source for alpha blending.
     * If backdrop was used as destination for alpha blending it won't be
     * anymore.
     */
    static void useBackdropAsAlphaSrc();

    /**
     * Use backdrop as source for alpha blending.
     * If backdrop was used as destination for alpha blending it won't be
     * anymore.
     */
    static void useBackdropAsAlphaDst();

    /**
     * Sets alpha blending mode for all backgrounds.
     * @param mode New alpha blending mode.
     */
    static void setAlphaBlendingMode(BackgroundAlphaBlendingMode mode);

    /**
     * Sets value for alpha blending coefficient A.
     * @param  coeff Value, unsigned from 0 to 16.
     * @return       Whether new value could be set or not.
     */
    static bool setAlphaBlendingCoefficientOne(uint8 coeff);

    /**
     * Sets value for alpha blending coefficient B.
     * @param  coeff Value, unsigned from 0 to 16.
     * @return       Whether new value could be set or not.
     */
    static bool setAlphaBlendingCoefficientTwo(uint8 coeff);

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

    /**
     * Displays information about this background.
     */
    void print();

    /**
     * Displays information about given tile of this background.
     * @param tile_id ID of tile whose information will be displayed.
     */
    void printTile(background_tile_id tile_id);

};

}

#endif