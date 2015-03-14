#ifndef CELL_H
#define CELL_H

#include <vector>

#include "./FMAW.h"
#include "./unit.h"

#include "./constants.h"

typedef struct t_indexPath {
    /**
     * Row pointed by this index path.
     */
    int row;
    /**
     * Column pointed by this index path.
     */
    int col;
} IndexPath;

bool operator <(IndexPath const &left, IndexPath const &right);

typedef enum t_cellBackgroundType {
    CellBGNone     = 0,
    CellBGWhite    = 1,
    CellBGBlack    = 2,
    // ----------------
    CellBGBase     = 3,
    CellBGBridge   = 4,
    CellBGForest   = 5,
    CellBGGrass    = 6,
    CellBGMountain = 7,
    CellBGRiver    = 8
} CellBackgroundType;

#define CELL_WIDTH  16
#define CELL_HEIGHT 16

class Cell {
  private:
    /**
     * Type of background of this cell.
     */
    CellBackgroundType backgroundType;
    /**
     * Position of the center of the cell in the screen.
     */
    FMAW::Point center;
    /**
     * Unit located at this cell.
     */
    Unit *characterInCell;

  public:
    /**
     * Creates an empty cell.
     */
    Cell();

    /**
     * Sets center of this cell.
     * @param newCenter New center of this cell.
     */
    void setCenter(FMAW::Point newCenter);

    /**
     * Background that will be used to draw this cell.
     */
    FMAW::Background background;

    /**
     * Tiles used to draw this cell.
     */
    std::vector<FMAW::background_tile_id> tiles;

    /**
     * Returns the background type of this cell.
     * @return Background type of this cell.
     */
    CellBackgroundType getBackgroundType();

    /**
     * Sets background type of this cell to given one.
     * @param type New background type of this cell.
     */
    void setBackgroundType(CellBackgroundType type);

    /**
     * Returns the position of the center of this cell in the screen.
     * @return Position of the center of this cell in the screen.
     */
    FMAW::Point getCenter();

    /**
     * Returns whether cell is occupied by a character (true) or not.
     * @return Whether cell is occupied by a character (true) or not.
     */
    bool isOccupied();

    /**
     * Returns the Unit occupying this cell.
     * @return Unit occupying this cell.
     */
    Unit *getCharacter();

    /**
     * Sets the Unit occupying this cell.
     * @param newCharacter New Unit that will occupy this cell.
     * @return Previous Unit occupying this cell.
     */
    Unit *setCharacter(Unit *newCharacter);

    /**
     * Cost of moving to this cell.
     * @return Cost of moving to this cell.
     */
    int movementCost();

    /**
     * Draws this cell's background.
     */
    void renderBackground();

    /**
     * Draws this cell's character.
     */
    void renderCharacter();
};

#endif