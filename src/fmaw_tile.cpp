// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./fmaw_tile.h"

#include <map>
#include <string>
#include "./fmaw_sprite.h"

//------------------------------------------------------------------------------
// Tile class.
//------------------------------------------------------------------------------

namespace FMAW {

std::map<int, int> Tile::IDtoImgMemoryPosition {};
int Tile::nextImgMemoryPosition = 0;
std::map<int, int> Tile::IDtoPalMemoryPosition {};
int Tile::nextPalMemoryPosition = 0;
int Tile::nextID = 0;

}  // namespace FMAW
