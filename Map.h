#ifndef MAP_H 
#define MAP_H
#endif

#include <string>
#include <iostream>

struct Map {

    int width, height;
    int tileWidth, tileHeight;
    Map (int w, int h, int tWidth, int tHeight) {
        width=w;
        height=h;
        tileWidth = tWidth;
        tileHeight = tHeight;
    }

};

    
