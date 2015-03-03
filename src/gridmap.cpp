// Copyright 2015 FMAW

#include <iostream>
#include <fstream>
#include "./grid.h"

namespace GridMap{

/**
 * Loads the default map into the given grid.
 * @param g       Grid in which to load the map.
 */
void loadDefaultGridMap( Grid g ) { loadGridMap("defaultMap", g); }

/**
 * Loads the map with given name into the given grid.
 * @param mapName Name of the map to load.
 * @param g       Grid in which to load the map.
 */ 
void loadGridMap( const char* mapName, Grid &g ){
	std::ifstream mapFile;
	mapFile.open( mapName );
	
	int rows, cols, aux;
	
	mapFile >> rows >> cols;
	for( int row = 0; i < rows; i++ ){
		for( int col = 0; j < cols; j++ ){
			mapFile >> aux;
			
			IndexPath path {row, col};
			g.cellAtIndexPath(path)->setBackgroundType( aux );
		}
	}
	
	mapFile.close();
}

}
