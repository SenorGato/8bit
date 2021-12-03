#ifndef MAP_H 
#define MAP_H
#endif

#include <string>
#include <iostream>
#include <vector>
#include "Tile.h"
class Map {

    public:
    int width, height;
    int tileWidth, tileHeight;
    std::vector<Tile> grid;
    Map (int w, int h, int tWidth, int tHeight);
    std::vector<Tile> init();
};

    
