#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Menu.h"

Menu::Menu(fontData *font, int height, std::string bgColor) {
        this->head = new menuItem{nullptr,""}; 
        this->font = font;
        this->height = height;
        this->bgColor = bgColor;
}

void Menu::initMenu(std::vector<std::string> keys, Menu *menu, menuItem* parent) {
    for(std::string key : keys) {
        parent->children.push_back (new menuItem{parent, key});
        parent->children.back()->renderedSurface = SDLisHard::renderText(key,menu->font);
    }
}

menuItem* Menu::fetchMenuItem(std::string key, menuItem* head){
//menuItem* foo = fetchMenuItem(key,child); if foo !=nullptr {return foo;} and return nullptr if it doesn't find the item.
    std::cout << "At the head of fetchMenuItem.  Head:" << head->key << std::endl;
    static menuItem* result;
    if(!head->children.empty()) {
        std::cout << "Are children." << std::endl;
        for(menuItem *child : head->children){
            std::cout << "Making recursive call:" << "Child:" << &child << std::endl;
            menuItem* result = fetchMenuItem(key,child);
        }
    } else {
        std::cout << "In else" << std::endl;
            if (result !=nullptr) {
                std::cout << "Returning result:" << result << std::endl;
                return result;
            } else {
                std::cout << "Returing nullptr" << std::endl;
                return nullptr;
            }

    }
}


