#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Menu.h"

Menu::Menu(fontData *font, int height, std::vector<int> bgColor) {
        this->font = font;
        this->height = height;
        this->bgColor = bgColor;
        this->head = new menuItem{nullptr,""}; 
}

void Menu::initMenu(std::vector<std::string> keys, Menu *menu, menuItem* parent) {
    for(std::string key : keys) {
        parent->children.push_back (new menuItem{parent, key});
        parent->children.back()->renderedSurface = SDLisHard::renderText(key,menu->font);
    }
}

menuItem* Menu::fetchMenuItem(std::string key, menuItem* head){
//menuItem* foo = fetchMenuItem(key,child); if foo !=nullptr {return foo;} and return nullptr if it doesn't find the item.
    std::cout << "At head of function.  Key:" << key << " Menuitemkey:"  << head->key << std::endl;
    if (head->key == key) {
        std::cout << "Key:" << head->key << std::endl;
        return head;
    }
    for (menuItem *child : head->children){
        std::cout << "Before Recursive call:" << child << std::endl;
        return fetchMenuItem(key,child);
    }
}
