#include <vector>
#include "Map.h"

Map::Map(int w, int h, int tWidth, int tHeight) {
        width = w;
        height = h;
        tileWidth = tWidth;
        tileHeight = tHeight;
}

std::vector<Tile> Map::init(){
       int numXTiles, numYTiles;
       numXTiles = width / tileWidth;
       numYTiles = height / tileHeight;
       for(int i; i< numXTiles; i++) {
               for(int p; p< numYTiles; p++) {
                        grid.push_back (Tile());
               }
       }
       return grid;
}

void Map::render(){



}

