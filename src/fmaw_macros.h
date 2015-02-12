#ifndef FMAW_MACROS
#define FMAW_MACROS

// Macro for calculating BG VRAM memory address with tile index.
#define tile2bgram(t)   (BG_GFX + (t) * 16)

// Macro for calculating BG VRAM memory address with palette index.
#define pal2bgram(p)    (BG_PALETTE + (p) * 16)

// Macro for calculating Sprite VRAM memory address with tile index.
#define tile2objram(t)  (SPRITE_GFX + (t) * 16)

// Macro for calculating Palette VRAM memory address with palette index.
#define pal2objram(p)   (SPRITE_PALETTE + (p) * 16)

// Returns the amount of frames that will be displayed in
#define frames_in_ms(x) (x / 16)

#endif