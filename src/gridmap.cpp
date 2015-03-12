// Copyright 2015 FMAW

#include <fat.h>
#include <nds.h>
#include <iostream>
#include <fstream>
#include "./grid.h"
#include "./gridmap.h"

namespace GridMap {

void loadDefaultGridMap(Grid &g) {
    loadGridMap("defaultMap", g);
}

void loadGridMap(const char *mapName, Grid &g) {
    FILE *test = fopen("./defaultMap", "r");

    if (test != NULL) {
        int rows, cols, aux;

        fscanf(test, "%d %d\n", &rows, &cols);
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (col < cols - 1) {
                    fscanf(test, "%d ", &aux);
                } else {
                    fscanf(test, "%d\n", &aux);
                }

                IndexPath path {row, col};
                g.cellAtIndexPath(path)->setBackgroundType(
                    static_cast<CellBackgroundType>(aux));

                g.cellAtIndexPath(path)->renderBackground();
            }
        }

        fclose(test);
    }
}

}  // namespace GridMap
