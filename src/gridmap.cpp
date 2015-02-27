// Copyright 2015 FMAW

#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "./gridmap.h"


//GridMap::GridMap() : GridMap("defaultMap") {}
GridMap::GridMap(const char* mapName){
	std::ifstream mapFile;
	mapFile.open( mapName );
	
	mapFile >> this->height >> this->width;
	this->mapMat = std::vector< std::vector<int> >(
		this->height, std::vector<int>(this->width)
	);
	for( int i = 0; i < this->height; i++ ){
		for( int j = 0; j < this->width; j++ ){
			mapFile >> this->mapMat[i][j];
		}
	}
	
	mapFile.close();
}

int GridMap::getPosition(int x, int y){
	if( x >= this->height || y >= this->width || x < 0 || y < 0 )
	    throw std::out_of_range("The requested position is "
								"out of the map boundaries.");
	
	return this->mapMat[x][y];
}

int GridMap::rows(){ return this->height; }
int GridMap::cols(){ return this->width; }
