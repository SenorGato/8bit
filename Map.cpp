#include <vector>
#include "Map.h"

Map::Map(int w, int h, int tWidth, int tHeight) {
        width = w;
        height = h;
        tileWidth = tWidth;
        tileHeight = tHeight;
}

std::vector<Tile> Map::init(){
        std::cout <<"In init loop\n";
       int numXTiles, numYTiles;
       numXTiles = width / tileWidth;
       numYTiles = height / tileHeight;
       for(int i = 0; i< numXTiles; i++) {
               for(int p = 0; p< numYTiles; p++) {
                        grid.push_back (Tile());
               }
       }
       return grid;
}

void Map::render(){



}

