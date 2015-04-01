#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <iostream>
#include <fstream>
#include <string>
#include "./grid.h"
#include "./gridmap.h"

namespace GridMap {

/**
 * Loads the default map into the given grid.
 * @param g       Grid in which to load the map.
 */
void loadDefaultGridMap(Grid *g);

/**
 * Loads the map with given name into the given grid.
 * @param mapName Name of the map to load.
 * @param g       Grid in which to load the map.
 */
void loadGridMap(std::string mapName, Grid *g);

}

#endif
