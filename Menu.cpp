#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Menu.h"

Menu::Menu(std::vector<std::string> keys, int height) {
    std::vector<std::string> k = keys;
    int h = height;
    std::vector<Menu> renderedMenu = initMenu(keys,height);
}

std::vector<Menu> Menu::initMenu(std::vector<std::string> keys, int height) {
    for (std::string key : keys) {
}

bool Menu::onClick() {
    return true;
}
