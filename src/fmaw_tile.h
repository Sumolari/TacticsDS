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

typedef enum t_tile_screen {
    ScreenMain,
    ScreenSub
} TileScreen;

typedef struct t_tile_attrib {
    const unsigned int *tilesArray;
    const int tilesLength;
    const unsigned short *paletteArray;
    const int paletteLength;
    const TileType type;
    const TileScreen screen;
    t_tile_attrib(const unsigned int *tilesArray,
                  const int tilesLength,
                  const unsigned short *paletteArray,
                  const int paletteLength,
                  const TileType type,
                  const TileScreen screen) :
        tilesArray(tilesArray),
        tilesLength(tilesLength),
        paletteArray(paletteArray),
        paletteLength(paletteLength),
        type(type),
        screen(screen) {}
} TileAttributes;

/**
 * Width in pixels of a tile.
 */
#define TILE_WIDTH  8

/**
 * Height in pixels of a tile.
 */
#define TILE_HEIGHT 8

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
     * Creates a new tile given the attributes defining the tile.
     */
    Tile(TileAttributes attributes);

    /**
     * Replaces tile with given ID with given attributes.
     */
    Tile(TileAttributes attributes, int ID);

    /**
     * Returns tile associated with given ID.
     */
    Tile(int ID);

};

}

#endif