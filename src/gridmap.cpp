// Copyright 2015 FMAW

#include <iostream>
#include <fstream>
#include <string>

#include "./FMAW.h"
#include "./grid.h"
#include "./gridmap.h"
#include "./unit.h"

namespace GridMap {

void loadDefaultGridMap(Grid *g) {
    loadGridMap("defaultMap", g);
}

void loadGridMap(std::string mapName, Grid *g) {
    FILE *test = FMAW::IO::fopen(("./maps/" + mapName).c_str(), "r");

    if (test != NULL) {
        int rows, cols, aux;

        FMAW::IO::fscanf(test, "%d %d\n", &rows, &cols);
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (col < cols - 1) {
                    FMAW::IO::fscanf(test, "%d ", &aux);
                } else {
                    FMAW::IO::fscanf(test, "%d\n", &aux);
                }

                IndexPath path {row, col};
                g->cellAtIndexPath(path)->setBackgroundType(
                    static_cast<CellBackgroundType>(aux));

                g->cellAtIndexPath(path)->renderBackground();
            }
        }

		FMAW::IO::fscanf(test, "\n");
		
		int owner, unitType, posx, posy;
		
		while (fscanf(test, "%d %d (%d, %d)", &owner, &unitType, &posx, &posy) != EOF) {
			Unit *u = Unit::UnitWithType(unitType, owner-1);
			g->cellAtIndexPath({posx-1, posy-1})->setCharacter(u);
		}
		
		g->resetUnitMovements();

        FMAW::IO::fclose(test);
    }
}

}  // namespace GridMap
