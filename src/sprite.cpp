#include <nds.h>
#include <nds/debug.h>

#include "./math.h"
#include "./sprite.h"

namespace FMAW {

//------------------------------------------------------------------------------
// Common sprite helpers.
//------------------------------------------------------------------------------

void clearAllSprites(void) {
    for ( sprite_id id = 0; id < TOTAL_SPRITES; id++ )
        disableSprite( id );
}

void disableSprite( sprite_id id ) {
    sprites[id].attr0 = ATTR0_DISABLED;
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
    if ( x != xCapped ) return false;

    // If x was negative we have to apply 2's complement.
    if ( isNegative ) x = twosComplement9B(x);

    // We have to set the upper part of the half-word to 1 so AND doesn't
    // break anything.
    x |= 0xFF00;
    // We have to set position's bits to 1 so we can then make an AND.
    this->entry.attr1 = this->entry.attr1 | 0x01FF;
    // Now we can set position with a simple AND.
    this->entry.attr1 &= x;

    return true;
}

bool Sprite::setYPosition( int y ) {
    bool isNegative = y < 0;
    if ( isNegative ) y = -y;

    uint16 yCapped = y & 0x007F;
    if ( y != yCapped ) return false;

    // If x was negative we have to apply 2's complement.
    if ( isNegative ) y = twosComplement8B(y);

    // We have to set the upper part of the half-word to 1 so AND doesn't
    // break anything.
    y |= 0xFF00;
    // We have to set position's bits to 1 so we can then make an AND.
    this->entry.attr0 = this->entry.attr0 | 0x00FF;
    // Now we can set position with a simple AND.
    this->entry.attr0 &= y;

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
    uint8 x = this->entry.attr1 & 0x01FF;
    // If x-position was a negative number...
    if ( (x & 0x0100) != 0 ) return -twosComplement9B(x);
    return x;
}

int Sprite::getYPosition() {
    uint8 y = this->entry.attr0 & 0x00FF;
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
    this->entry.attr2 |= 0x01FF;
    // We apply and AND to set the bits properly.
    this->entry.attr2 &= tileIndexCapped;
    return true;
}

bool Sprite::setPalette( uint8 paletteIndex ) {
    uint8 paletteIndexCapped = paletteIndex & 0x000F;
    if ( paletteIndex != paletteIndexCapped ) return false;
    // We first set tile bits to 1 so we can apply an AND later.
    this->entry.attr2 |= 0xF000;
    // We apply and AND to set the bits properly.
    this->entry.attr2 &= paletteIndexCapped << 12;
    return true;
}

//----------//------------------------------------------------------------------
//----------// Other settings.
//----------//------------------------------------------------------------------

void Sprite::disable() {
    // _TODO: Update this method to ensure that previous settings are preserved.
    this->entry.attr0 = ATTR0_DISABLED;
}

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
    this->entry.attr0 |= 0XC000;
    this->entry.attr1 |= 0XC000;
    // And then we apply the mask.
    this->entry.attr0 &= attr0mask;
    this->entry.attr1 &= attr1mask;

    return true;
}

SpriteSizeMode Sprite::getSizeMode() {
    uint16 shape = this->entry.attr0 & 0xC000;
    uint16 size  = this->entry.attr1 & 0xC000;
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

}