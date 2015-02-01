// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include <nds.h>
#include <nds/debug.h>
#include <sstream>

#include "./FMAW.h"  // Import our awesome framework!

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------

#include "./gfx_ball.h"
#include "./gfx_brick.h"
#include "./gfx_gradient.h"

//------------------------------------------------------------------------------
// Background tile entries
//------------------------------------------------------------------------------

#define TILE_EMPTY     0  // Tile 0 = empty
#define TILE_BRICK     1  // Tile 1 = brick
#define TILE_GRADIENT  2  // Tile 2 = gradient

// Macro for calculating BG VRAM memory address with tile index.
#define tile2bgram(t)  (BG_GFX + (t) * 16)

//------------------------------------------------------------------------------
// Background...
//------------------------------------------------------------------------------

//----------//------------------------------------------------------------------
//----------// Palette entries
//----------//------------------------------------------------------------------

#define PAL_BRICKS     0  // Brick palette (entry 0->15).
#define PAL_GRADIENT   1  // Gradient palette (entry 16->31).

#define BACKDROP_COLOR RGB8(190, 255, 255)

// Macro for calculating BG VRAM memory address with palette index.
#define pal2bgram(p)   (BG_PALETTE + (p) * 16)

//----------//------------------------------------------------------------------
//----------// Screen base blocks pointed
//----------//------------------------------------------------------------------

#define bg0map    (reinterpret_cast<u16*>BG_MAP_RAM(1))
#define bg1map    (reinterpret_cast<u16*>BG_MAP_RAM(2))

//------------------------------------------------------------------------------
// Sprites...
//------------------------------------------------------------------------------

//----------//------------------------------------------------------------------
//----------// Tile entries
//----------//------------------------------------------------------------------

#define TILES_BALL     0  // Ball tiles (16x16 tile: 0 -> 3)

// Macro for calculating Sprite VRAM memory address with tile index.
#define tile2objram(t) (SPRITE_GFX + (t) * 16)

//----------//------------------------------------------------------------------
//----------// Palette entries
//----------//------------------------------------------------------------------

#define PAL_BALL       0  // Ball palette (entry 0 -> 15)

// Macro for calculating Palette VRAM memorya address with palette index.
#define pal2objram(p) (SPRITE_PALETTE + (p) * 16)

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

    // Copy Sprites graphics.
    dmaCopyHalfWords(3, gfx_ballTiles, tile2objram(TILES_BALL),
                     gfx_ballTilesLen);

    // BG palettes go to palette memory.
    dmaCopyHalfWords(3, gfx_brickPal, pal2bgram(PAL_BRICKS), gfx_brickPalLen);
    dmaCopyHalfWords(3, gfx_gradientPal, pal2bgram(PAL_GRADIENT),
                     gfx_gradientPalLen);

    // Sprite palettes go to palette memory.
    dmaCopyHalfWords(3, gfx_ballPal, pal2objram(PAL_BALL), gfx_ballPalLen);

    // Set backdrop color.
    BG_PALETTE[0] = BACKDROP_COLOR;

    // libnds prefixes the register names with REG_
    REG_BG0CNT  = BG_MAP_BASE(1);
    REG_BG1CNT  = BG_MAP_BASE(2);

    videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE |
                 DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT);

    FMAW::clearAllSprites();

    // Add some sprites.
    for ( int n = 0; n < 5; n++ ) {
        FMAW::Sprite sprite;
        sprite.setXPosition(rand() % 256);
        sprite.setYPosition(rand() % 192);
        sprite.setSizeMode(FMAW::square16x16);
        sprite.setTile(TILES_BALL);
        sprite.setPalette(PAL_BALL);
        sprite.enable();
    }
}

void update_logic() {
}

void update_graphics() {
    // Clear entire bricks' tilemap and gradient's tilemap to zero
    for ( int n = 0; n < 1024; n++ ) {
        bg0map[n] = 0;
        bg1map[n] = 0;
    }

    // Set tilemap entries for 6 first rows of background 0 (bricks).
    for ( int y = 0; y < 6; y++ ) {
        int y32 = y * 32;

        for ( int x = 0; x < 32; x++ ) {
            // Magical formula to calculate if the tile needs to be flipped.
            // Basically: x & 1 -> AND operation between both numbers, that is:
            //            if last bit is 1, 1, if not, 0. This allows to check
            //            if a number is odd or even in a very fast way.
            //            y & 1 -> Works in the very same way as x & 1.
            //            ^ is the xor operator.
            int hflip = (x & 1) ^ (y & 1);

            // Set the tilemap entry.
            // (PAL_BRICKS << 12) remains there because it is computed at
            // compile time!
            bg0map[x + y32] = TILE_BRICK | (hflip << 10) | (PAL_BRICKS << 12);
        }
    }
    // Did we say 6 first rows? We wanted 6 LAST rows!
    REG_BG0VOFS = 112;

    // Set tilemap entries for 8 first rows of background 1 (gradient).
    for ( int y = 0; y < 8; y++ ) {
        int tile = TILE_GRADIENT + y;
        int y32 = y * 32;

        for ( int x = 0; x < 32; x++ )
            bg1map[x + y32] = tile | (PAL_GRADIENT << 12);
    }

    // Enable alpha blending of background 1.
    // My guess: BLEND_DST_BACKDROP is the 14th bit at 1, BLEND_SRC_BG1 is the
    //           2nd bit at 1 and BLEND_ALPHA are bits 8th and 7th at 10.
    //           BLEND_DST_BACKDROP 0010000000000000
    //           BLEND_SRC_BG1      0000000000000010
    //           BLEND_ALPHA        0000000010000000
    //           -----------------------------------
    //                              0010000010000010
    REG_BLDCNT = BLEND_ALPHA | BLEND_SRC_BG1 | BLEND_DST_BACKDROP;
    REG_BLDALPHA = (4) + (16 << 8);  // This is computed at compile time.
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
