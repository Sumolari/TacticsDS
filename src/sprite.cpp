#include <string>

#include <nds.h>
#include <nds/debug.h>

#include "./math.h"
#include "./sprite.h"
#include "./debug.h"

namespace FMAW {

//------------------------------------------------------------------------------
// Common sprite helpers.
//------------------------------------------------------------------------------

void clearAllSprites() {
    for ( sprite_id id = 0; id < TOTAL_SPRITES; id++ ) {
        Sprite sprite (id);
        sprite.clear();
    }
}

//------------------------------------------------------------------------------
// Sprite class.
//------------------------------------------------------------------------------

uint8 Sprite::nextEmptySprite = 0;

//----------//------------------------------------------------------------------
//----------// Position.
//----------//------------------------------------------------------------------

bool Sprite::setXPosition( int x ) {
    bool isNegative = x < 0;
    if ( isNegative ) x = -x;

    uint16 xCapped = x & 0x00FF;
    printf("X Original: %d New: %u", x, xCapped);
    if ( x != xCapped ) return false;

    // If x was negative we have to apply 2's complement.
    if ( isNegative ) x = twosComplement9B(x);

    // We have to set the upper part of the half-word to 1 so AND doesn't
    // break anything.
    x |= 0xFE00;
    // We have to set position's bits to 1 so we can then make an AND.
    sprites[this->id].attr1 |= 0x01FF;
    // Now we can set position with a simple AND.
    sprites[this->id].attr1 &= x;

    return true;
}

bool Sprite::setYPosition( int y ) {
    bool isNegative = y < 0;
    if ( isNegative ) y = -y;

    uint16 yCapped = y & 0x007F;
    printf("Y Original: %d New: %u", y, yCapped);
    if ( y != yCapped ) return false;

    // If x was negative we have to apply 2's complement.
    if ( isNegative ) y = twosComplement8B(y);

    // We have to set the upper part of the half-word to 1 so AND doesn't
    // break anything.
    y |= 0xFF00;
    // We have to set position's bits to 1 so we can then make an AND.
    sprites[this->id].attr0 |= 0x00FF;
    // Now we can set position with a simple AND.
    sprites[this->id].attr0 &= y;

    return true;
}

bool Sprite::setPosition( int x, int y ) {
    Point previousPosition = this->getPosition();
    if ( this->setXPosition( x ) && this->setYPosition( y ) ) return true;
    else {
        this->setXPosition( previousPosition.x );
        this->setYPosition( previousPosition.y );
        return false;
    }
    return true;
}

bool Sprite::setPosition( Point point ) {
    return this->setPosition( point.x, point.y );
}

int Sprite::getXPosition() {
    uint8 x = sprites[this->id].attr1 & 0x01FF;
    // If x-position was a negative number...
    if ( (x & 0x0100) != 0 ) return -twosComplement9B(x);
    return x;
}

int Sprite::getYPosition() {
    uint8 y = sprites[this->id].attr0 & 0x00FF;
    // If y-position was a negative number...
    if ( (y & 0x0080) != 0 ) return -twosComplement8B(y);
    return y;
}

Point Sprite::getPosition() {
    Point p {};
    p.x = this->getXPosition();
    p.y = this->getYPosition();
    return p;
}

//----------//------------------------------------------------------------------
//----------// Tile & palette settings.
//----------//------------------------------------------------------------------

bool Sprite::setTile( uint16 tileIndex ) {
    uint16 tileIndexCapped = tileIndex & 0x01FF;
    if ( tileIndex != tileIndexCapped ) return false;
    // We first set tile bits to 1 so we can apply an AND later.
    sprites[this->id].attr2 |= 0x01FF;
    // We apply and AND to set the bits properly.
    sprites[this->id].attr2 &= tileIndexCapped;
    return true;
}

uint16 Sprite::getTile() {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Sprite::setPalette( uint8 paletteIndex ) {
    uint8 paletteIndexCapped = paletteIndex & 0x000F;
    if ( paletteIndex != paletteIndexCapped ) return false;
    // We first set tile bits to 1 so we can apply an AND later.
    sprites[this->id].attr2 |= 0xF000;
    // We apply and AND to set the bits properly.
    sprites[this->id].attr2 &= paletteIndexCapped << 12;
    return true;
}

uint8 Sprite::getPalette() {
    TO_BE_IMPLEMENTED
    return 0;
}

//----------//------------------------------------------------------------------
//----------// Rotation & scale settings.
//----------//------------------------------------------------------------------

/**
 * Enables rotation and scale of this sprite.
 */
void Sprite::enableRotationAndScale() {
    TO_BE_IMPLEMENTED
}

/**
 * Disables rotation and scale of this sprite.
 * Double-size will be disabled, too.
 */
void Sprite::disableRotationAndScale() {
    TO_BE_IMPLEMENTED
}

/**
 * Returns whether rotation and scaling are enabled in this sprite or not.
 * @return Whether rotation and scaling are enabled in this sprite or not.
 */
bool Sprite::rotationAndScaleAreEnabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Sprite::rotationAndScaleAreDisabled() {
    return !this->rotationAndScaleAreEnabled();
}

/**
 * Enables double size of this sprite.
 * Will enable also rotation and scaling.
 */
void Sprite::enableDoubleSize() {
    TO_BE_IMPLEMENTED
}

/**
 * Disables double size of this sprite.
 */
void Sprite::disableDoubleSize() {
    TO_BE_IMPLEMENTED
}

/**
 * Returns whether double size is enabled or not.
 * @return Whether double size is enabled or not.
 */
bool Sprite::doubleSizeEnabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Sprite::doubleSizeDisabled() {
    return !this->doubleSizeEnabled();
}

//----------//------------------------------------------------------------------
//----------// Object mode settings.
//----------//------------------------------------------------------------------

/**
 * Sets this sprite's object mode to given one.
 * @param newMode This sprite's object mode.
 */
void Sprite::setObjectMode( SpriteObjectMode newMode ) {
    TO_BE_IMPLEMENTED
}

/**
 * Returns this sprite's object mode.
 * @return Object mode of this sprite.
 */
SpriteObjectMode Sprite::getObjectMode() {
    TO_BE_IMPLEMENTED
    return normal;
}

//----------//------------------------------------------------------------------
//----------// Mosaic & color settings.
//----------//------------------------------------------------------------------

void Sprite::enableMosaic() {
    TO_BE_IMPLEMENTED
}

void Sprite::disableMosaic() {
    TO_BE_IMPLEMENTED
}

bool Sprite::mosaicIsEnabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Sprite::mosaicIsDisabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

void Sprite::use16BitColors() {
    TO_BE_IMPLEMENTED
}

void Sprite::use256BitColors() {
    TO_BE_IMPLEMENTED
}

bool Sprite::isUsing16BitColors()
{
    TO_BE_IMPLEMENTED
    return 0;
}

bool Sprite::isUsing256BitColors() {
    return !this->isUsing16BitColors();
}

//----------//------------------------------------------------------------------
//----------// Shape & size settings.
//----------//------------------------------------------------------------------

bool Sprite::setSizeMode( SpriteSizeMode newMode ) {
    uint16 attr0mask;
    uint16 attr1mask;

    switch ( newMode ) {
        case square8x8:
        case square16x16:
        case square32x32:
        case square64x64:
            attr0mask = 0x3FFF;
            break;
        case wide16x8:
        case wide32x8:
        case wide32x16:
        case wide64x32:
            attr0mask = 0x7FFF;
            break;
        case tall8x16:
        case tall8x32:
        case tall16x32:
        case tall32x64:
            attr0mask = 0xBFFF;
            break;
        default:
            return false;
    }

    switch ( newMode ) {
        case square8x8:
        case wide16x8:
        case tall8x16:
            attr1mask = 0x3FFF;
            break;
        case square16x16:
        case wide32x8:
        case tall8x32:
            attr1mask = 0x7FFF;
            break;

        case square32x32:
        case wide32x16:
        case tall16x32:
            attr1mask = 0xBFFF;
            break;
        case square64x64:
        case wide64x32:
        case tall32x64:
            attr1mask = 0xFFFF;
            break;
        default:
            return false;
    }

    // We first set the size bits to 1.
    sprites[this->id].attr0 |= 0XC000;
    sprites[this->id].attr1 |= 0XC000;
    // And then we apply the mask.
    sprites[this->id].attr0 &= attr0mask;
    sprites[this->id].attr1 &= attr1mask;

    return true;
}

SpriteSizeMode Sprite::getSizeMode() {
    uint16 shape = sprites[this->id].attr0 & 0xC000;
    uint16 size  = sprites[this->id].attr1 & 0xC000;
    SpriteSizeMode sizeMode;

    switch ( shape ) {
        // Square.
        case 0x0000:
            switch (size) {
                case 0x0000:
                    sizeMode = square8x8;
                    break;
                case 0x4000:
                    sizeMode = square16x16;
                    break;
                case 0x8000:
                    sizeMode = square32x32;
                    break;
                case 0xC000:
                    sizeMode = square64x64;
                    break;
                default:
                    sizeMode = unknown;
                    break;
            }
            break;
        // Wide.
        case 0x4000:
            switch (size) {
                case 0x0000:
                    sizeMode = wide16x8;
                    break;
                case 0x4000:
                    sizeMode = wide32x8;
                    break;
                case 0x8000:
                    sizeMode = wide32x16;
                    break;
                case 0xC000:
                    sizeMode = wide64x32;
                    break;
                default:
                    sizeMode = unknown;
                    break;
            }
            break;
        // Tall.
        case 0x8000:
            switch (size) {
                case 0x0000:
                    sizeMode = tall8x16;
                    break;
                case 0x4000:
                    sizeMode = tall8x32;
                    break;
                case 0x8000:
                    sizeMode = tall16x32;
                    break;
                case 0xC000:
                    sizeMode = tall32x64;
                    break;
                default:
                    sizeMode = unknown;
                    break;
            }
            break;
        // Not used.
        case 0xC000:
        default:
            sizeMode = unknown;
            break;
    }

    return sizeMode;
}

//----------//------------------------------------------------------------------
//----------// Flip settings.
//----------//------------------------------------------------------------------

/**
 * Enables horizontal flip for this sprite.
 * This will disable rotation/scale for this sprite.
 */
void Sprite::enableHorizontalFlip() {
    TO_BE_IMPLEMENTED
}

/**
 * Disables horizontal flip for this sprite.
 * This will disable rotation/scale for this sprite.
 */
void Sprite::disableHorizontalFlip() {
    TO_BE_IMPLEMENTED
}

/**
 * Returns whether horizontal flip is enabled for this sprite or not.
 * If rotation/scaling is disabled it'll return false.
 * @return Whether horizontal flip is enabled for this sprite or not.
 */
bool Sprite::horizontalFlipIsEnabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

/**
 * Returns whether horizontal flip is disabled for this sprite or not.
 * If rotation/scaling is disabled it'll return false.
 * THIS IS NOT EQUIVALENT TO !horizontalFlipIsEnabled() !!
 * @return Whether horizontal flip is disabled for this sprite or not.
 */
bool Sprite::horizontalFlipIsDisabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

/**
 * Enables vertical flip for this sprite.
 * This will disable rotation/scale for this sprite.
 */
void Sprite::enableVerticalFlip() {
    TO_BE_IMPLEMENTED
}

/**
 * Disables vertical flip for this sprite.
 * This will disable rotation/scale for this sprite.
 */
void Sprite::disableVerticalFlip() {
    TO_BE_IMPLEMENTED
}

/**
 * Returns whether vertical flip is enabled for this sprite or not.
 * If rotation/scaling is disabled it'll return false.
 * @return Whether vertical flip is enabled for this sprite or not.
 */
bool Sprite::verticalFlipIsEnabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

/**
 * Returns whether vertical flip is disabled for this sprite or not.
 * If rotation/scaling is disabled it'll return false.
 * THIS IS NOT EQUIVALENT TO !verticalFlipIsEnabled() !!
 * @return Whether vertical flip is disabled for this sprite or not.
 */
bool Sprite::verticalFlipIsDisabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

//----------//------------------------------------------------------------------
//----------// Priority settings.
//----------//------------------------------------------------------------------

void Sprite::setPriority( SpritePriority priority ) {
    TO_BE_IMPLEMENTED
}

SpritePriority Sprite::getPriority() {
    TO_BE_IMPLEMENTED
    return spLOW;
}

//----------//------------------------------------------------------------------
//----------// Other settings.
//----------//------------------------------------------------------------------

void Sprite::clear() {
    sprites[this->id].attr0 = ATTR0_DISABLED;
    sprites[this->id].attr1 = 0;
    sprites[this->id].attr2 = 0;
    sprites[this->id].affine_data = 0;
}

void Sprite::disable() {
    uint16 disableMask = 0xFEFF;
    sprites[this->id].attr0 &= disableMask;
}

void Sprite::enable() {
    uint16 enableMask = 0xFCFF;
    sprites[this->id].attr0 &= enableMask;
}

void Sprite::print() {
    FMAW::printf("%s\r\n  Sprite %u:%s\r\n|%s|",
                 "\r\n|----------------|", this->id, "\r\n|----------------|",
                 half_word_to_binary(sprites[this->id].attr0).c_str());
    FMAW::printf("|%s|\r\n|%s|",
                 half_word_to_binary(sprites[this->id].attr1).c_str(),
                 half_word_to_binary(sprites[this->id].attr2).c_str());
    FMAW::printf("|%s|\r\n%s",
                 half_word_to_binary(sprites[this->id].affine_data).c_str(),
                 "|----------------|");
}

}