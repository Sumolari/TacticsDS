// Copyright 2015 FMAW

#include <iostream>
#include <fstream>
#include "./grid.h"

namespace GridMap{

void loadDefaultGridMap( Grid g ) { loadGridMap("defaultMap", g); }

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
