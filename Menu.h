#ifndef MENU_H
#define MENU_H
#endif

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Fontdata.h"
#include "SDLisHard.h"

struct menuItem {
    menuItem* parent;
    std::vector<menuItem*> children;
    std::string key;
    SDL_Texture* renderedSurface;

    menuItem(menuItem* parent, std::string key) {
    };
};

class Menu {
    public:
    menuItem *head;
    fontData *font;
    int height;
    std::string bgColor;
    static void initMenu(std::vector<std::string> keys, Menu *menu, menuItem* parent);
    static menuItem* fetchMenuItem(std::string key, menuItem* head);

    Menu(fontData *font, int height, std::string bgColor);
};

