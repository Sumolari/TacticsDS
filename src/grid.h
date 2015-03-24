#ifndef GRID_H
#define GRID_H

#include <vector>
#include <map>
#include <string>
#include <functional>

#include "./cell.h"
#include "./cursor.h"

class Grid {
  private:
    /**
     * Cells in the grid.
     */
    std::vector<Cell> cells;

    /**
     * Amount of rows in this grid.
     */
    int rows;

    /**
     * Amount of columns in this grid.
     */
    int cols;

    /**
     * Currently selected cell's path.
     */
    IndexPath selectedPath;

    /**
     * Currently picked up cell's path.
     */
    IndexPath pickedUpCell;

    /**
     * Sprite of the cursor to indicate which cell is selected.
     */
    Cursor cursor;

    /**
     * ID of the callback triggered when down arrow is released.
     */
    int downArrowCallbackID;

    /**
     * ID of the callback triggered when up arrow is released.
     */
    int upArrowCallbackID;

    /**
     * ID of the callback triggered when left arrow is released.
     */
    int leftArrowCallbackID;

    /**
     * ID of the callback triggered when right arrow is released.
     */
    int rightArrowCallbackID;

    /**
     * ID of the callback triggered when A button is released.
     */
    int aButtonCallbackID;

    /**
     * ID of the callback triggered when B button is released.
     */
    int bButtonCallbackID;

    /**
     * Cells rechables by currently selected unit.
     */
    std::map<IndexPath, bool> reachableCells;

    /**
     * Cells attackable by currently selected unit.
     */
    std::map<IndexPath, bool> attackableCells;

    /**
     * Recomputes the cells reachable by currently selected unit.
     * If no unit is selected all cells are available.
     */
    void recomputeReachableCells();

    /**
     * Recomputes the cells attackable by currently selected unit.
     * If no unit is selected no cells are available.
     */
    void recomputeAttackableCells();

    /**
     * Returns whether some cell with a character has been picked up or not.
     * @return Whether some cell with a character has been picked up or not.
     */
    bool hasPickedUpCell();

    /**
     * File where game will be saved.
     */
    FILE *savefile;

    /**
     * Whether grid is currently playing a saved file or not.
     */
    bool playingSavedFile;

    /**
     * ID of sound to be played when a cell is selected.
     */
    int selectSoundID;

    /**
     * ID of sound to be played when a non-interactible cell is selected.
     */
    int forbiddenSoundID;

    /**
     * ID of sound to be played when an attack is performed.
     */
    int hitSoundID;

  public:

    /**
     * Callback called when game is over.
     * Parameter is the winner.
     */
    std::function<void(int)> gameOverCallback;

    /**
     * Creates a new grid.
     */
    Grid();

    /**
     * Enables saving history so any movement in the grid will be saved.
     * @param filename File where history will be saved.
     * @return         Whether file can be used to save history or not.
     */
    bool enableSavingHistory(std::string filename);

    /**
     * Plays saved history.
     * @param filename File where history is located.
     * @param callback Function to be called when history has been played.
     *                 Argument will be true on success.
     */
    void playSavedHistory(std::string filename,
                          std::function<void(bool)> callback);

    /**
     * Removes all units from this grid.
     */
    void clearGridUnits();

    /**
     * Returns whether a saved file is being played or not.
     * @return Whether a saved file is being played or not.
     */
    bool isPlayingSavedFile();

    /**
     * Returns whether interaction with this grid is enabled or not.
     * @return Whether interaction with this grid is enabled or not.
     */
    bool isInteractionEnabled();

    /**
     * Resets available movements for all units in the grid.
     */
    void resetUnitMovements();

    /**
     * Initializes cursor.
     */
    void initCursor();

    /**
     * Returns cell located at given IndexPath.
     * @param  ip IndexPath, location of the cell.
     * @return    Cell located at given path.
     */
    Cell *cellAtIndexPath(IndexPath ip);

    /**
     * Returns cell located at currently selected path.
     * @return Cell located at currently selected path.
     */
    Cell *cellAtSelectedPath();

    /**
     * Returns the currently selected cell's index path.
     * @return Index path of currently selected cell.
     */
    IndexPath getSelectedPath();

    /**
     * Moves the attacking character in given cell to attacked 
     * character at given cell and returns, simulating an attack.
     * @param  attackerPos      Original cell of the attacking character.
     * @param  victimPos        Final cell of the attacked character.
     * @param  duration         Duration of the animation.
     * @return                  Whether change could be performed or not.
     */
    bool attackCharacterAtCell(IndexPath attackerPos, IndexPath victimPos,
                                     unsigned int duration);
    
    /**
     * Moves the character in given cell to given cell.
     * @param  from      Original cell of the character.
     * @param  to        Final cell of the character.
     * @param  duration  Duration of the animation.
     * @return           Whether change could be performed or not.
     */
    bool moveCharacterFromCellToCell(IndexPath from, IndexPath to,
                                     unsigned int duration);

    /**
     * Returns whether AI should be able to move given character from given cell
     * to given cell.
     * @param  from      Original cell of the character.
     * @param  to        Final cell of the character.
     * @return           Whether change could be performed or not.
     */
    bool canMoveCharacterFromCellToCell(IndexPath from, IndexPath to);

    /**
     * Draws the grid and the cells.
     */
    void renderBackground();

    /**
     * Draws the characters in the cells.
     */
    void renderCharacters();

    /**
     * Returns the amount of rows in this grid.
     * @return Amount of rows in this grid.
     */
    int numRows();

    /**
     * Returns the amount of columns in this grid.
     * @return Amount of columns in this grid.
     */
    int numCols();

    /**
     * Returns whether there exists at least one character of given user in the
     * grid or not.
     * @param  owner ID of the owner.
     * @return       True if there exists at least one character of given user.
     */
    bool existCharacterWithOwner(int owner);

    //--------------------------------------------------------------------------
    // Cell selection.
    //--------------------------------------------------------------------------

    /**
     * Sets selected cell.
     * If index is out of bounds it'll do nothing and return false.
     * @param  path Path of new selected cell.
     * @return      Whether selected cell changed or not.
     */
    bool selectCellAtIndexPath(IndexPath path);

    /**
     * Selects cell at bottom of previous cell.
     * If new index is out of bounds it'll do nothing and return false.
     * If no previous cell was selected will return false and do nothing.
     * @return Whether selected cell changed or not.
     */
    bool selectBottomCell();

    /**
     * Selects cell at top of previous cell.
     * If new index is out of bounds it'll do nothing and return false.
     * If no previous cell was selected will return false and do nothing.
     * @return Whether selected cell changed or not.
     */
    bool selectTopCell();

    /**
     * Selects cell at left of previous cell.
     * If new index is out of bounds it'll do nothing and return false.
     * If no previous cell was selected will return false and do nothing.
     * @return Whether selected cell changed or not.
     */
    bool selectLeftCell();

    /**
     * Selects cell at right of previous cell.
     * If new index is out of bounds it'll do nothing and return false.
     * If no previous cell was selected will return false and do nothing.
     * @return Whether selected cell changed or not.
     */
    bool selectRightCell();

    //--------------------------------------------------------------------------
    // Cursor settings.
    //--------------------------------------------------------------------------

    /**
     * Sets the cursor to be an arrow.
     */
    void setArrowCursor();

    /**
     * Sets the cursor to be an square.
     */
    void setSquareCursor();

    /**
     * Sets the cursor to be a cross.
     */
    void setCrossCursor();

    /**
     * Sets the cursor to be a sword.
     */
    void setSwordCursor();

    /**
     * Resets picked up cell so no cell is selected.
     */
    void resetPickedUpCell();

    //--------------------------------------------------------------------------
    // Callbacks.
    //--------------------------------------------------------------------------

    /**
     * Enqueues all callbacks to manage user input.
     */
    void enqueueCallbacks();

    /**
     * Dequeues callbacks to manage user input.
     */
    void dequeueCallbacks();
};

#endif
