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

bool Sprite::setXPosition( int x ) {
    bool isNegative = x < 0;
    if ( isNegative ) x = -x;

    uint16 xCapped = x & 0x7F;
    if ( x != xCapped ) return false;

    // If x was negative we have to apply 2's complement.
    if ( isNegative ) x = twosComplement(x);

    // We have to set position's bits to 1 so we can then make an AND.
    this->entry.attr1 = this->entry.attr1 | 0xFF;

    // Now we can set position with a simple AND.
    this->entry.attr1 &= x;

    return true;
}

bool Sprite::setYPosition( int y ) {
    bool isNegative = y < 0;
    if ( isNegative ) y = -y;

    uint16 yCapped = y & 0x7F;
    if ( y != yCapped ) return false;

    // If x was negative we have to apply 2's complement.
    if ( isNegative ) y = twosComplement(y);

    // We have to set position's bits to 1 so we can then make an AND.
    this->entry.attr0 = this->entry.attr0 | 0xFF;

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
    uint8 x = this->entry.attr1 & 0xFF;

    // If x-position was a negative number...
    if ( (x & 0x80) != 0 ) {
        x = twosComplement(x);
        return -x;
    }

    return x;
}

int Sprite::getYPosition() {
    uint8 y = this->entry.attr0 & 0xFF;

    // If y-position was a negative number...
    if ( (y & 0x80) != 0 ) {
        y = twosComplement(y);
        return -y;
    }

    return y;
}

Point Sprite::getPosition() {
    Point p {};
    p.x = this->getXPosition();
    p.y = this->getYPosition();
    return p;
}

}