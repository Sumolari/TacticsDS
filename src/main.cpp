// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include <nds.h>

void update_logic() {
}

void update_graphics() {
}

int main(void) {
    irqInit();               // Initialize interrups.
    irqEnable(IRQ_VBLANK);   // Enable vblank interrupt.
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
