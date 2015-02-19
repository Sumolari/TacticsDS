// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./FMAW.h"
#include <nds.h>

namespace FMAW {

void init() {
    irqInit();               // Initialize interrups.
    irqEnable(IRQ_VBLANK);   // Enable vblank interrupt.

    vramSetBankE(VRAM_E_MAIN_BG);
    vramSetBankF(VRAM_F_MAIN_SPRITE);

    Timer::init();
    clearAllSprites();

    videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE | DISPLAY_BG1_ACTIVE |
                 DISPLAY_SPR_ACTIVE | DISPLAY_SPR_1D_LAYOUT);
}

}  // namespace FMAW
