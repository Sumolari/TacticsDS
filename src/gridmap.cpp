// Copyright 2015 FMAW


// Add method FMAW::fopen();
// Add method FMAW::fclose();
// Add method FMAW::fscanf();
// Add method FMAW::fprintf();

#include <iostream>
#include <fstream>
#include "./FMAW.h"
#include "./grid.h"
#include "./gridmap.h"

namespace GridMap {

void loadDefaultGridMap(Grid *g) {
    loadGridMap("defaultMap", g);
}

void loadGridMap(const char *mapName, Grid *g) {
    FILE *test = FMAW::IO::fopen("./defaultMap", "r");

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

        FMAW::IO::fclose(test);
    }
}

}  // namespace GridMap
