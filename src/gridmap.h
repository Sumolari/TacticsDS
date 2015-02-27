#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <vector>

class GridMap{
    private:
      int width;
      int height;
      std::vector< std::vector<int> > mapMat;
    
    public:
      /*
       * Loads the default map.
       */
      //GridMap();
      /*
       * Loads the map with the given name.
       * @param: mapName  Name of the map to be loaded.
       */
      GridMap(const char* mapName);
      
      /*
       * Returns the number stored in the corresponding indexes.
       * @param  x  Row of the GridMap to retrieve.
       * @param  y  Column of the GridMap to retrieve.
       * @return    Element at (x, y) on the map matrix.
       */ 
      int getPosition(int x, int y);
      
      /*
       * Returns the number of rows of the map.
       * @return    Height of the map.
       */
      int rows();
      /*
       * Returns the number of columns of the map.
       * @return    Width of the map.
       */
      int cols();
};

#endif
