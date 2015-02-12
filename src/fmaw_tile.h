#ifndef FMAW_TILE_H
#define FMAW_TILE_H

#include <map>
#include <string>
#include "./fmaw_macros.h"
#include "./fmaw_debug.h"
#include "./fmaw_sprite.h"

namespace FMAW {

typedef struct t_tile_attrib {
    const unsigned int *tilesArray;
    const int tilesLength;
    const unsigned short *paletteArray;
    const int paletteLength;
} TileAttributes;

//------------------------------------------------------------------------------
// Tile class.
//------------------------------------------------------------------------------

class Tile {
private:
    /**
     * Tile's ID -> tile's image memory position mapping.
     */
    static std::map<int, int> IDtoImgMemoryPosition;
    /**
     * First memory position available for tiles.
     */
    static int nextImgMemoryPosition;

    /**
     * Tile's ID -> tile's palette memory position mapping.
     */
    static std::map<int, int> IDtoPalMemoryPosition;
    /**
     * First memory position available for tiles.
     */
    static int nextPalMemoryPosition;

public:
    /**
     * Creates a new tile given the ID that will be used to refer to this tile.
     */
    Tile(int ID, TileAttributes attributes) {
        typedef Tile self;

        FMAW::printf("I'm copying tiles of length %d to %d",
                     attributes.tilesLength,
                     self::nextImgMemoryPosition);

        // Copy to memory.
        dmaCopyHalfWords(3,
                         attributes.tilesArray,
                         tile2objram(self::nextImgMemoryPosition),
                         attributes.tilesLength);

        dmaCopyHalfWords(3,
                         attributes.paletteArray,
                         pal2objram(self::nextPalMemoryPosition),
                         attributes.paletteLength);

        // Store memory address of this tile.
        self::IDtoImgMemoryPosition[ID] = self::nextImgMemoryPosition;
        self::IDtoPalMemoryPosition[ID] = self::nextPalMemoryPosition;
        // Move pointer so next tile will be stored properly.
        // This is equivalent to: attributes.tilesLength / 32
        self::nextImgMemoryPosition += attributes.tilesLength >> 5;
        // TODO: Update this to handle multiple size palettes.
        self::nextPalMemoryPosition++;
    };
};

}

#endif