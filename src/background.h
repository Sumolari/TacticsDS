#ifndef FMAW_BACKGROUND_H
#define FMAW_BACKGROUND_H

namespace FMAW {

#define TOTAL_BACKGROUNDS 4  // Total amount of backgrounds that can be rendered.

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
     * Constructor for Sprite with given ID. Sprite should have been previously
     * created otherwise results are not defined.
     */
    Background( background_id id ) : id(id) {};

    //--------------------------------------------------------------------------
    // Main settings.
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

    bool setCharacterBaseBlock( uint8 characterBaseBlock );

    uint8 getCharacterBaseBlock();

    void enableMosaic();

    void disableMosaic();

    bool mosaicIsEnabled();

    bool mosaicIsDisabled();

    void use16BitColors();

    void use256BitColors();

    bool isUsing16BitColors();

    bool isUsing256BitColors();

    bool setScreenBaseBlock( uint8 newScreenBaseBlock );

    uint8 getScreenBaseBlock();

    void enableDisplayAreaOverflow();

    void disableDisplayAreaOverflow();

    bool displayAreaOverflowEnabled();

    bool setSize( BackgroundSize newSize );

    BackgroundSize getSize();

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