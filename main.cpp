#include <SDL2/SDL.h>
#include <string>
#include <cstdio>
#include <iostream>
#include "Map.h"

int main (int argc, char* argv[]) {

    int width = 800;
    int height = 800;
    int tileWidth = 10;
    int tileHeight = 10;

    Map gamestate(800,800,10,10);
    gamestate.init();
    
//    std::cout << "gamestate.grid:" << gamestate.grid << std::endl;
    std::cout << "grid.size():" << gamestate.grid.size() << std::endl;

//    for(int i = 0; i < (width/tileWidth); i++) {
//        if (i% = 0) {
//            gamestate.sprite = "1";
//        } else {
//            gamestate.sprite= "2";
//
//        }
}
