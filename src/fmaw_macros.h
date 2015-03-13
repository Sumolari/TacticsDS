#ifndef FMAW_MACROS
#define FMAW_MACROS

#ifdef NDS

#include <nds.h>

// Macro for calculating BG VRAM memory address with tile index (main engine).
#define tile2bgram(t)   (BG_GFX + (t) * 16)

// Macro for calculating BG VRAM memory address with palette index
// (main engine).
#define pal2bgram(p)    (BG_PALETTE + (p) * 16)

// Macro for calculating Sprite VRAM memory address with tile index
// (main engine).
#define tile2objram(t)  (SPRITE_GFX + (t) * 16)

// Macro for calculating Palette VRAM memory address with palette index
// (main engine).
#define pal2objram(p)   (SPRITE_PALETTE + (p) * 16)

// Macro for calculating BG VRAM memory address with tile index (sub engine).
#define tile2bgramSub(t)   (BG_GFX_SUB + (t) * 16)

// Macro for calculating BG VRAM memory address with palette index (sub engine).
#define pal2bgramSub(p)    (BG_PALETTE_SUB + (p) * 16)

// Macro for calculating Sprite VRAM memory address with tile index
// (sub engine).
#define tile2objramSub(t)  (SPRITE_GFX_SUB + (t) * 16)

// Macro for calculating Palette VRAM memory address with palette index
// (sub engine).
#define pal2objramSub(p)   (SPRITE_PALETTE_SUB + (p) * 16)

// Returns the amount of frames that will be displayed in
#define frames_in_ms(x) (x / 16)

#endif

#endif