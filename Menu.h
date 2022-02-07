#ifndef MENU_H
#define MENU_H

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
    bool isVisible;
    bool onClick();
    bool onHover();

    menuItem(menuItem* parent, std::string key) {
        this->key = key;
        this->parent = parent;
    }
};

class Menu {
    public:
    menuItem *head;
    fontData *font;
    int height;
    std::vector<int> bgColor;
    void initMenu(std::vector<std::string> keys, menuItem* parent);
    menuItem* fetchMenuItem(std::string key, menuItem* head);
    void addElement(std::string key, menuItem *head);
    void deleteElement(menuItem *dest);
    menuItem* renderMenu(menuItem* head);

    Menu(fontData *font, int height, std::vector<int> bgColor);
};
#endif
