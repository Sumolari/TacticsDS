#ifndef MAIN_MENU_H
#define MAIN_MENU_H

namespace MainMenu {

/**
 * Renders the main menu.
 */
void render();

/**
 * Moves main menu to touch screen.
 */
void makeMenuForeground();

/**
 * Moves main menu to non-touch screen.
 */
void makeMenuBackground();

/**
 * Enqueues callbacks for main menu handling.
 */
void enqueueMenuCallbacks();

/**
 * Dequeues callbacks for main menu handling.
 */
void dequeueMenuCallbacks();

}  // namespace MainMenu

#endif