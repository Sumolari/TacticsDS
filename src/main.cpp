// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include <nds.h>

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------

#include "./gfx_ball.h"
#include "./gfx_brick.h"
#include "./gfx_gradient.h"

//------------------------------------------------------------------------------
// Tile entries
//------------------------------------------------------------------------------

#define TILE_EMPTY     0  // Tile 0 = empty
#define TILE_BRICK     1  // Tile 1 = brick
#define TILE_GRADIENT  2  // Tile 2 = gradient

// Macro for calculating BG VRAM memory address with tile index.
#define tile2bgram(t)  (BG_GFX + (t) * 16)

//------------------------------------------------------------------------------
// Palette entries
//------------------------------------------------------------------------------

#define PAL_BRICKS     0  // Brick palette (entry 0->15).
#define PAL_GRADIENT   1  // Gradient palette (entry 16->31).

#define BACKDROP_COLOR RGB8(190, 255, 255)

// Macro for calculating BG VRAM memory address with palette index.
#define pal2bgram(p)   (BG_PALETTE + (p) * 16)

//------------------------------------------------------------------------------
// Main code section
//------------------------------------------------------------------------------

/**
 * Sets up graphics.
 */
void setupGraphics(void) {
    vramSetBankE(VRAM_E_MAIN_BG);
    vramSetBankF(VRAM_F_MAIN_SPRITE);

    // Generate the first blank tile by clearing it to zero.
    for ( int n = 0; n < 16; n++ )
        BG_GFX[n] = 0;

    // Copy BG graphics.
    dmaCopyHalfWords(3, gfx_brickTiles, tile2bgram(TILE_BRICK),
                     gfx_brickTilesLen);
    dmaCopyHalfWords(3, gfx_gradientTiles, tile2bgram(TILE_GRADIENT),
                     gfx_gradientTilesLen);

    // Palettes go to palette memory.
    dmaCopyHalfWords(3, gfx_brickPal, pal2bgram(PAL_BRICKS), gfx_brickPalLen);
    dmaCopyHalfWords(3, gfx_gradientPal, pal2bgram(PAL_GRADIENT),
                     gfx_gradientPalLen);

    // Set backdrop color.
    BG_PALETTE[0] = BACKDROP_COLOR;
}

void update_logic() {
}

void update_graphics() {
    videoSetMode(MODE_0_2D);
}

int main(void) {
    irqInit();               // Initialize interrups.
    irqEnable(IRQ_VBLANK);   // Enable vblank interrupt.
    setupGraphics();
    while (1) {
        // Rendering period:
        // Update game objects.
        update_logic();

        // Wait for the vblank period.
        swiWaitForVBlank();

        // VBlank period: (safe yo modify graphics)
        // Move the graphics around.
        update_graphics();
    }
}
