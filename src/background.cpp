#include <nds.h>

#include "./background.h"
#include "./debug.h"

namespace FMAW {

//------------------------------------------------------------------------------
// Background class.
//------------------------------------------------------------------------------

background_id Background::nextEmptyBackground = 0;

vu16 *Background::tilemap() {
    return (reinterpret_cast<u16 *>BG_MAP_RAM(this->id));
}

vu16 *Background::reg() {
    switch ( this->id ) {
        case 0:
            return &REG_BG0CNT;
        case 1:
            return &REG_BG1CNT;
        case 2:
            return &REG_BG2CNT;
        case 3:
        default:
            return &REG_BG3CNT;
    }
}

//----------//------------------------------------------------------------------
//----------// Position.
//----------//------------------------------------------------------------------

bool Background::setCharacterBaseBlock( uint8 characterBaseBlock ) {
    if ( characterBaseBlock > 15 || characterBaseBlock < 0 ) return false;
    characterBaseBlock <<= 2;
    *this->reg() &= 0xFFC3;
    *this->reg() |= characterBaseBlock;
    return true;
}

uint8 Background::getCharacterBaseBlock() {
    return (*this->reg() & 0x003C) >> 2;
}

bool Background::setScreenBaseBlock( uint8 newScreenBaseBlock ) {
    if ( newScreenBaseBlock > 31 || newScreenBaseBlock < 0 ) return false;
    newScreenBaseBlock <<= 8;
    *this->reg() &= 0xE0FF;
    *this->reg() |= newScreenBaseBlock;
    return true;
}

uint8 Background::getScreenBaseBlock() {
    return (*this->reg() & 0x1F00) >> 8;
}

void Background::enableDisplayAreaOverflow() {
    *this->reg() |= 0x2000;
}

void Background::disableDisplayAreaOverflow() {
    *this->reg() &= 0xDFFF;
}

bool Background::displayAreaOverflowEnabled() {
    return (*this->reg() &= 0x2000) != 0;
}

bool Background::displayAreaOverflowDisabled() {
    return !this->displayAreaOverflowEnabled();
}

//----------//------------------------------------------------------------------
//----------// Tile & palette settings.
//----------//------------------------------------------------------------------

bool Background::setTile( background_tile_id tile_id, uint16 tileIndex ) {
    TO_BE_IMPLEMENTED
    return 0;
}

uint16 Background::getTile( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Background::setPalette( background_tile_id tile_id, uint8 paletteIndex ) {
    TO_BE_IMPLEMENTED
    return 0;
}

uint8 Background::getPalette( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
    return 0;
}

//----------//------------------------------------------------------------------
//----------// Mosaic & color settings.
//----------//------------------------------------------------------------------

void Background::enableMosaic() {
    TO_BE_IMPLEMENTED
}

void Background::disableMosaic() {
    TO_BE_IMPLEMENTED
}

bool Background::mosaicIsEnabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Background::mosaicIsDisabled() {
    TO_BE_IMPLEMENTED
    return 0;
}

void Background::use16BitColors() {
    TO_BE_IMPLEMENTED
}

void Background::use256BitColors() {
    TO_BE_IMPLEMENTED
}

bool Background::isUsing16BitColors() {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Background::isUsing256BitColors() {
    TO_BE_IMPLEMENTED
    return 0;
}

//----------//------------------------------------------------------------------
//----------// Shape & size settings.
//----------//------------------------------------------------------------------

void Background::setSize( BackgroundSize newSize ) {
    TO_BE_IMPLEMENTED
}

BackgroundSize Background::getSize() {
    TO_BE_IMPLEMENTED
    return size32x32;
}

//----------//------------------------------------------------------------------
//----------// Flip settings.
//----------//------------------------------------------------------------------

void Background::enableHorizontalFlip( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
}

void Background::disableHorizontalFlip( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
}

bool Background::horizontalFlipIsEnabled( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Background::horizontalFlipIsDisabled( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
    return 0;
}

void Background::enableVerticalFlip( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
}

void Background::disableVerticalFlip( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
}

bool Background::verticalFlipIsEnabled( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
    return 0;
}

bool Background::verticalFlipIsDisabled( background_tile_id tile_id ) {
    TO_BE_IMPLEMENTED
    return 0;
}

//----------//------------------------------------------------------------------
//----------// Priority settings.
//----------//------------------------------------------------------------------

void Background::setPriority( BackgroundPriority priority ) {
    TO_BE_IMPLEMENTED
}

BackgroundPriority Background::getPriority() {
    TO_BE_IMPLEMENTED
    return bpHIGHEST;
}

//----------//------------------------------------------------------------------
//----------// Other settings.
//----------//------------------------------------------------------------------

void Background::clear() {
    TO_BE_IMPLEMENTED
}

void Background::clearAllTiles() {
    TO_BE_IMPLEMENTED
}

}