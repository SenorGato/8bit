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

void Menu::initMenu(std::vector<std::string> keys, menuItem* parent) {
    for(std::string key : keys) {
        parent->children.push_back (new menuItem{parent, key});
        parent->children.back()->renderedSurface = SDLisHard::renderText(key,this->font);
    }
}

menuItem* Menu::fetchMenuItem(std::string key, menuItem* head){
    if (head->key == key) {
        return head;
    }
    for (menuItem *child : head->children){
        menuItem *foo = fetchMenuItem(key,child);
        if (foo !=nullptr) {
            return foo;
        }     
    }
    return nullptr;
}

menuItem* Menu::renderMenu(menuItem* head){
    if (head->renderedSurface != nullptr) {
        return head;
    }
    for (menuItem *child : head->children){
        child->renderedSurface = SDLisHard::renderText(child->key,this->font);
        std::cout << "In child loop.  Child->renderedSurface:" << child->renderedSurface << " Child key:" << child->key << std::endl; 
        menuItem *foo = renderMenu(child);
        if (foo !=nullptr) {
            return foo;
        }     
    }
    return nullptr;
}

void Menu::addElement(std::string key, menuItem *head){
    head->children.push_back(new menuItem (head, key));
    renderMenu(head);
}

void Menu::deleteElement(menuItem *dest) {
    for(int i=0; i < dest->parent->children.size(); i++) {
        if(dest->key == dest->parent->children[i]->key){
            dest->parent->children.erase(dest->parent->children.begin());
        }
    }
}

   //So if we build a surface for each level upfront, and set its positional data
   //Then we can just toggle visibility
   //
   //If (menu->head->key == NULL) {
   //   for (child : menu->head->children) {
   //      child->renderedSurface = renderText(key,menu->font);
   //   }
   //} else {
   //   Your at child level, render
   //}

