#ifndef MENU_H
#define MENU_H
#endif

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


class Menu {
	
	public:
    std::string keys;
	int height;
    SDL_Surface* menuSurface;
    Menu(std::vector<std::string> keys, int height);
    std::vector<Menu> initMenu(std::vector<std::string> keys, int height);
    bool onClick(); 
};
