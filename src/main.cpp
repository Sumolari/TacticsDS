// Copyright 2015 FMAW

#include "./FMAW.h"  // Import our awesome framework!

//------------------------------------------------------------------------------
// Graphic references
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Background...
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Game objects
//------------------------------------------------------------------------------

FMAW::FixedReal g_camera_x;
FMAW::FixedReal g_camera_y;

//------------------------------------------------------------------------------
// Main code section
//------------------------------------------------------------------------------

/**
 * Sets up graphics.
 */
void setupGraphics(void) {
}

/**
 * Updates game logic.
 */
void update_logic() {
    FMAW::Timer::check();
}

/**
 * Renders graphics.
 */
void update_graphics() {
    FMAW::Camera::setHorizontalOffset(g_camera_x);
}

/**
 * Main.
 */
int main(void) {
    FMAW::init(update_graphics, update_logic);
    setupGraphics();

    FMAW::start();

    return 0;
}
