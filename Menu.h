#ifndef MENU_H
#define MENU_H
#endif

#include <string>
#include <vector>

class Menu {
	
	public:
	SDL_Surface* menuSurface;
	std::vector<std::string> keys;
	int height;
	Menu(SDL_Surface* dest, std::vector<std::string> keys, int h);
	SDL_Rect buildMenu(SDL_Surface * dest, int h);
};
