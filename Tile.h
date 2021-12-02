#ifndef TILE_H
#define TILE_H
#endif

#include <string>
#include <iostream>

struct Point {int x; int y;};

struct Tile {

    Point pos;
    int width, height;
    std::string sprite;
    bool isWalkable;
};

    
