#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "./FMAW.h"

class MainMenu {
  private:

    /**
     * Whether main menu is currently on foreground screen or not.
     */
    bool menuCurrentlyOnForegroundScreen;

    /**
     * Whether main menu background tile changed after last time it was
     * rendered or not.
     */
    bool menuChangedBackgroundTile;

    /**
     * ID of touch callback.
     */
    int touchCallbackID;

    /**
     * ID of up arrow callback.
     */
    int upArrowCallbackID;

    /**
     * ID of down arrow callback.
     */
    int downArrowCallbackID;

    /**
     * ID of A button callback;
     */
    int aButtonCallbackID;

    /**
     * Background used to draw Main Menu.
     */
    FMAW::Background background;

    /**
     * Tile for logo when playing blue player.
     */
    FMAW::TileAttributes logo_attributes_blue;

    /**
     * Tile for logo when playing red player.
     */
    FMAW::TileAttributes logo_attributes_red;

    /**
     * Tile for main menu with no selected option.
     */
    FMAW::TileAttributes main_menu_attributes;

    /**
     * Tile for main menu with New Game selected.
     */
    FMAW::TileAttributes main_menu_new_game_attributes;

    /**
     * Tile for main menu with Load Game selected.
     */
    FMAW::TileAttributes main_menu_load_game_attributes;

    /**
     * Tile for main menu with Versus selected.
     */
    FMAW::TileAttributes main_menu_versus_attributes;

    /**
     * Tile for main menu when blue player wins.
     */
    FMAW::TileAttributes winner_blue_attributes;

    /**
     * Tile for main menu when red player wins.
     */
    FMAW::TileAttributes winner_red_attributes;

    /**
     * ID of tile used to draw menu's background.
     */
    int backgroundTileID;

    /**
     * Tile that should be currently displayed.
     */
    FMAW::Tile current_tile;

    /**
     * Currently selected menu option.
     */
    int currentlySelectedOption;

  public:

    /**
     * Callback called when New Game button is released.
     */
    std::function<void(void)> newGameCallback;

    /**
     * Callback called when Load Game button is released.
     */
    std::function<void(void)> loadGameCallback;

    /**
     * Callback called when Versus button is released.
     */
    std::function<void(void)> versusCallback;

    /**
     * Initializes the Main Menu.
     */
    MainMenu();

    /**
     * Loads main menu assets.
     */
    void init();

    /**
     * Changes currently selected tile to match user's selected option.
     */
    void adjustCurrentTile();

    /**
     * Renders the main menu.
     */
    void render();

    /**
     * Moves main menu to touch screen.
     */
    void makeForeground();

    /**
     * Moves main menu to non-touch screen.
     */
    void makeBackground();

    /**
     * Returns whether menu is on foreground or not.
     * @return Whether menu is on foreground or not.
     */
    bool isInForeground();

    /**
     * Enqueues callbacks for main menu handling.
     */
    void enqueueCallbacks();

    /**
     * Dequeues callbacks for main menu handling.
     */
    void dequeueCallbacks();

};

#endif