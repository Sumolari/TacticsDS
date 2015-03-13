#ifndef GRID_H
#define GRID_H

#include <vector>

#include "./cell.h"

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

  public:
    /**
     * Creates a new grid.
     */
    Grid();

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
     * Moves the character in given cell to given cell.
     * @param  from      Original cell of the character.
     * @param  to        Final cell of the character.
     * @param  duration  Duration of the animation.
     * @return           Whether change could be performed or not.
     */
    bool moveCharacterFromCellToCell(IndexPath from, IndexPath to,
                                     unsigned int duration);

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
};

#endif