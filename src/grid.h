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
};

#endif