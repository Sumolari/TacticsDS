#ifndef CELL_H
#define CELL_H

#include <vector>

#include "./FMAW.h"

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

typedef enum t_cellBackgroundType {
    CellBGNone = 0,
    CellBGWhite = 1,
    CellBGBlack = 2,
    // -------------
    CellBGBase = 3,
    CellBGBridge = 4,
    CellBGForest = 5,
    CellBGGrass = 6,
    CellBGMountain = 7,
    CellBGRiver = 8
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
     * Character located at this cell.
     */
    FMAW::Character *characterInCell;

  public:
    /**
     * Creates an empty cell.
     */
    Cell();

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
     * Returns the character occupying this cell.
     * @return Character occupying this cell.
     */
    FMAW::Character *getCharacter();

    /**
     * Sets the character occupying this cell.
     * @param newCharacter New character that will occupy this cell.
     * @return Previous character occupying this cell.
     */
    FMAW::Character *setCharacter(FMAW::Character *newCharacter);

    /**
     * Draws this cell's background.
     */
    void renderBackground();
};

#endif