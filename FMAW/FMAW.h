#ifndef FMAW_H
#define FMAW_H

// Macro for calculating Sprite VRAM memory address with tile index.
#define tile2objram(t) (SPRITE_GFX + (t) * 16)

// Macro for calculating Palette VRAM memorya address with palette index.
#define pal2objram(p) (SPRITE_PALETTE + (p) * 16)

#include "./fmaw_types.h"
#include "./fmaw_math.h"
#include "./fmaw_geometry.h"
#include "./fmaw_debug.h"
#include "./fmaw_background.h"
#include "./fmaw_sprite.h"

#endif