#ifndef FMAW_MACROS
#define FMAW_MACROS

// Macro for calculating Sprite VRAM memory address with tile index.
#define tile2objram(t) (SPRITE_GFX + (t) * 16)

// Macro for calculating Palette VRAM memory address with palette index.
#define pal2objram(p) (SPRITE_PALETTE + (p) * 16)

#endif