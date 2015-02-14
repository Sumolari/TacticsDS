#ifndef FMAW_TILE_H
#define FMAW_TILE_H

#include <map>
#include <string>
#include "./fmaw_macros.h"
#include "./fmaw_debug.h"

namespace FMAW {

typedef enum t_tile_type {
    TypeBackground,
    TypeSprite
} TileType;

typedef struct t_tile_attrib {
    const unsigned int *tilesArray;
    const int tilesLength;
    const unsigned short *paletteArray;
    const int paletteLength;
    const TileType type;
} TileAttributes;

//------------------------------------------------------------------------------
// Tile class.
//------------------------------------------------------------------------------

class Tile {
    typedef Tile self;
private:
    /**
     * Tile's ID -> tile's image memory position mapping.
     */
    static std::map<int, int> IDtoImgMemoryPosition;
    /**
     * First memory position available for sprite tiles images.
     */
    static int nextSpriteImgMemoryPosition;
    /**
     * First memory position available for background tiles images.
     */
    static int nextBackgroundImgMemoryPosition;

    /**
     * Tile's ID -> tile's palette memory position mapping.
     */
    static std::map<int, int> IDtoPalMemoryPosition;
    /**
     * First memory position available for sprite tiles palette.
     */
    static int nextSpritePalMemoryPosition;
    /**
     * First memory position available for background tiles palette.
     */
    static int nextBackgroundPalMemoryPosition;

    /**
     * First ID available for tiles of any type.
     */
    static int nextID;

public:
    /**
     * Memory address for image data of this tile.
     */
    int imgMemory;

    /**
     * Memory address for palette data of this tile.
     */
    int palMemory;

    /**
     * ID of this tile.
     */
    int ID;

    /**
     * Creates a new tile given the ID that will be used to refer to this tile.
     */
    Tile(TileAttributes attributes) {

        if (attributes.type == TypeSprite) {
            this->imgMemory = self::nextSpriteImgMemoryPosition;
            this->palMemory = self::nextSpritePalMemoryPosition;
            // Move pointer so next tile will be stored properly.
            // This is equivalent to: attributes.tilesLength / 32
            self::nextSpriteImgMemoryPosition += attributes.tilesLength >> 5;
            // TODO: Update this to handle multiple size palettes.
            self::nextSpritePalMemoryPosition++;
        } else {
            this->imgMemory = self::nextBackgroundImgMemoryPosition;
            this->palMemory = self::nextBackgroundPalMemoryPosition;
            // Move pointer so next tile will be stored properly.
            // This is equivalent to: attributes.tilesLength / 32
            self::nextBackgroundImgMemoryPosition += attributes.tilesLength >> 5;
            // TODO: Update this to handle multiple size palettes.
            self::nextBackgroundPalMemoryPosition++;
        }


        FMAW::printf("I'm copying tiles of length %d to %d",
                     attributes.tilesLength, this->imgMemory);

        if (attributes.type == TypeSprite) {
            // Copy to memory.
            dmaCopyHalfWords(3,
                             attributes.tilesArray,
                             tile2objram(this->imgMemory),
                             attributes.tilesLength);

            dmaCopyHalfWords(3,
                             attributes.paletteArray,
                             pal2objram(this->palMemory),
                             attributes.paletteLength);
        } else {
            // Copy to memory.
            dmaCopyHalfWords(3,
                             attributes.tilesArray,
                             tile2bgram(this->imgMemory),
                             attributes.tilesLength);

            dmaCopyHalfWords(3,
                             attributes.paletteArray,
                             pal2bgram(this->palMemory),
                             attributes.paletteLength);
        }

        this->ID = this->nextID;

        // Store memory address of this tile.
        self::IDtoImgMemoryPosition[ID] = this->imgMemory;
        self::IDtoPalMemoryPosition[ID] = this->palMemory;
        // This ID has been used!
        self::nextID++;
    };

    /**
     * Returns tile associated with given ID.
     */
    Tile(int ID) {
        this->ID = ID;
        this->imgMemory = self::IDtoImgMemoryPosition[ID];
        this->palMemory = self::IDtoPalMemoryPosition[ID];
    }

};

}

#endif