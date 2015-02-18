// Copyright 2015 FMAW

#include <nds.h>

#include "./fmaw_background.h"

#include "./fmaw_types.h"
#include "./fmaw_tile.h"
#include "./fmaw_debug.h"

namespace FMAW {

void setBackgroundColor(unsigned int color) {
    BG_PALETTE[0] = color;
}

//------------------------------------------------------------------------------
// Background class.
//------------------------------------------------------------------------------

background_id Background::nextEmptyBackground = 0;

//----------//------------------------------------------------------------------
//----------// Position.
//----------//------------------------------------------------------------------

bool Background::setCharacterBaseBlock(uint8 characterBaseBlock) {
    if (characterBaseBlock > 15 || characterBaseBlock < 0) return false;
    *this->reg &= 0xFFC3;
    *this->reg |= characterBaseBlock << 2;
    return true;
}

uint8 Background::getCharacterBaseBlock() {
    return (*this->reg & 0x003C) >> 2;
}

bool Background::setScreenBaseBlock(uint8 newScreenBaseBlock) {
    if (newScreenBaseBlock > 31 || newScreenBaseBlock < 0) return false;
    *this->reg &= 0xE0FF;
    *this->reg |= newScreenBaseBlock << 8;
    this->tiles = reinterpret_cast<u16 *>BG_MAP_RAM(newScreenBaseBlock);
    return true;
}

uint8 Background::getScreenBaseBlock() {
    return (*this->reg & 0x1F00) >> 8;
}

void Background::enableDisplayAreaOverflow() {
    *this->reg |= 0x2000;
}

void Background::disableDisplayAreaOverflow() {
    *this->reg &= 0xDFFF;
}

bool Background::displayAreaOverflowEnabled() {
    return (*this->reg &= 0x2000) != 0;
}

bool Background::displayAreaOverflowDisabled() {
    return !this->displayAreaOverflowEnabled();
}

void Background::setVerticalOffset(uint8 offset) {
    *this->vOffset = offset;
}

uint8 Background::getVerticalOffset() {
    return *this->vOffset;
}

void Background::setHorizontalOffset(uint8 offset) {
    *this->hOffset = offset;
}

uint8 Background::getHorizontalOffset() {
    return *this->hOffset;
}

//----------//------------------------------------------------------------------
//----------// Tile & palette settings.
//----------//------------------------------------------------------------------

bool Background::setTile(background_tile_id tile_id, Tile tile) {
    return this->setTile(tile_id, tile.imgMemory)
           && this->setPalette(tile_id, tile.palMemory);
}

bool Background::setTile(background_tile_id tile_id, uint16 tileIndex) {
    uint16 tileIndexCapped = tileIndex & 0x01FF;
    if (tileIndex != tileIndexCapped) return false;
    this->tiles[tile_id] &= 0xFE00;
    this->tiles[tile_id] |= tileIndexCapped;
    return true;
}

uint16 Background::getTile(background_tile_id tile_id) {
    return this->tiles[tile_id] & 0x01FF;
}

bool Background::setPalette(background_tile_id tile_id, uint8 paletteIndex) {
    uint16 paletteIndexCapped = paletteIndex & 0x000F;
    if (paletteIndex != paletteIndexCapped) return false;
    this->tiles[tile_id] &= 0x0FFF;
    this->tiles[tile_id] |= paletteIndexCapped << 12;
    return true;
}

uint8 Background::getPalette(background_tile_id tile_id) {
    return (this->tiles[tile_id] & 0xF000) >> 12;
}

//----------//------------------------------------------------------------------
//----------// Mosaic & color settings.
//----------//------------------------------------------------------------------

void Background::enableMosaic() {
    *this->reg |= 0x0040;
}

void Background::disableMosaic() {
    *this->reg &= 0xFFCF;
}

bool Background::mosaicIsEnabled() {
    return (*this->reg & 0x0040) != 0;
}

bool Background::mosaicIsDisabled() {
    return !this->mosaicIsEnabled();
}

void Background::use16BitColors() {
    *this->reg &= 0xFF7F;
}

void Background::use256BitColors() {
    *this->reg |= 0x0080;
}

bool Background::isUsing16BitColors() {
    return (*this->reg & 0x0080) == 0;
}

bool Background::isUsing256BitColors() {
    return !this->isUsing16BitColors();
}

//----------//------------------------------------------------------------------
//----------// Shape & size settings.
//----------//------------------------------------------------------------------

void Background::setSize(BackgroundSize newSize) {
    *this->reg &= 0x3FFF;
    *this->reg |= newSize;
}

BackgroundSize Background::getSize() {
    uint16 halfword = *this->reg | 0x3FFF;
    switch (halfword) {
        case size32x32:
            return size32x32;
        case size64x32:
            return size64x32;
        case size32x64:
            return size32x64;
        case size64x64:
        // Default will not be triggered
        default:
            return size64x64;
    }
}

//----------//------------------------------------------------------------------
//----------// Flip settings.
//----------//------------------------------------------------------------------

void Background::enableHorizontalFlip(background_tile_id tile_id) {
    this->tiles[tile_id] |= 0x0400;
}

void Background::disableHorizontalFlip(background_tile_id tile_id) {
    this->tiles[tile_id] &= 0xFBFF;
}

bool Background::horizontalFlipIsEnabled(background_tile_id tile_id) {
    return (this->tiles[tile_id] & 0x0400) != 0;
}

bool Background::horizontalFlipIsDisabled(background_tile_id tile_id) {
    return !this->horizontalFlipIsEnabled(tile_id);
}

void Background::enableVerticalFlip(background_tile_id tile_id) {
    this->tiles[tile_id] |= 0x0800;
}

void Background::disableVerticalFlip(background_tile_id tile_id) {
    this->tiles[tile_id] &= 0xF7FF;
}

bool Background::verticalFlipIsEnabled(background_tile_id tile_id) {
    return (this->tiles[tile_id] & 0x0800) != 0;
}

bool Background::verticalFlipIsDisabled(background_tile_id tile_id) {
    return this->verticalFlipIsEnabled(tile_id);
}

//----------//------------------------------------------------------------------
//----------// Priority settings.
//----------//------------------------------------------------------------------

void Background::setPriority(BackgroundPriority priority) {
    *this->reg |= 0x0003;
    *this->reg &= priority;
}

BackgroundPriority Background::getPriority() {
    switch ((*this->reg & 0x0003) | 0xFFFC) {
        case bpHIGHEST:
            return bpHIGHEST;
        case bpHIGH:
            return bpHIGH;
        case bpLOW:
            return bpLOW;
        case bpLOWEST:
        // Default won't be triggered.
        default:
            return bpLOWEST;
    }
}

//----------//------------------------------------------------------------------
//----------// Other settings.
//----------//------------------------------------------------------------------

void Background::clear() {
    *this->reg = 0x0000;
}

void Background::clearAllTiles() {
    for (int n = 0; n < 1024; n++)
        this->tiles[n] = 0;
}

void Background::print() {
    printf("\r\nBackground %u: %s\r\n",
           this->id, half_word_to_binary(*this->reg).c_str());
}

void Background::printTile(background_tile_id tile_id) {
    printf("\r\nBackground %u, tile %u: %s\r\n",
           this->id, tile_id,
           half_word_to_binary(this->tiles[tile_id]).c_str());
}

}  // namespace FMAW
