// Copyright 2015 FMAW

#include "./fmaw_tile.h"

#include <map>
#include <string>
#include "./fmaw_sprite.h"

//------------------------------------------------------------------------------
// Tile class.
//------------------------------------------------------------------------------

namespace FMAW {

std::map<int, int> Tile::IDtoImgMemoryPosition {};
int Tile::nextSpriteImgMemoryPosition = 0;
int Tile::nextBackgroundImgMemoryPosition = 1;
std::map<int, int> Tile::IDtoPalMemoryPosition {};
int Tile::nextSpritePalMemoryPosition = 0;
int Tile::nextBackgroundPalMemoryPosition = 1;
int Tile::nextID = 0;

}  // namespace FMAW
