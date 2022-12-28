#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Menu.h"
#include "SDLisHard.h"

Menu::Menu(fontData *font, int height, std::vector<int> bgColor, SDL_Window* win, SDL_Renderer* rend) {
        this->font = font;
        this->height = height;
        this->bgColor = bgColor;
        this->win = win;
        this->rend = rend;
        this->head = new menuItem{nullptr,""}; 
}

void Menu::initMenu(std::vector<std::string> keys, menuItem* parent) {
    for(std::string key : keys) {
        parent->children.push_back (new menuItem{parent, key});
        parent->children.back()->texture = SDLisHard::renderText(key,this->font);
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
    if (head->children.empty()) {
        return head;
    }
    for (menuItem *child : head->children){
        child->texture = SDLisHard::renderText(child->key,this->font);
        std::cout << "In child loop.  Child->Texture:" << child->texture << " Child key:" << child->key << std::endl; 
        SDL_RenderClear(this->rend);
        SDL_RenderCopy(this->rend, child->texture, NULL, NULL);
        SDL_RenderPresent(this->rend);
        int n = 0;
        std::cin >> n; 
        renderMenu(child);
    }
    return nullptr;
}

void Menu::addElement(std::string key, menuItem *head){
    head->children.push_back(new menuItem (head, key));
    renderMenu(head);
}

void Menu::deleteElement(menuItem *dest) {
    for(unsigned long int i=0; i < dest->parent->children.size(); i++) {
        if(dest->key == dest->parent->children[i]->key){
            dest->parent->children.erase(dest->parent->children.begin());
        }
    }
}
SDL_Texture* Menu::buildChildren(menuItem* parent){
    std::cout << "In buildChildren" << std::endl;
    int canvasWidth = 0;
    int canvasHeight = 0;
    unsigned long x = 0;
    if (parent->key == "") {
        std::cout << "In head render" << std::endl;
        canvasHeight = this->height;
        for(menuItem* child : parent->children) {
            std::cout << "In width loop:" << canvasWidth << " ChildKey:" << child->key << std::endl;
            canvasWidth = child->key.size() + canvasWidth;
            }
        } else {
            std::cout << "In child render" << std::endl;
            canvasHeight = this->height * parent->children.size();
            for(menuItem* child : parent->children) {
                if (child->key.size() > x) {
                    canvasWidth = child->key.size();
                }
            }
        }
    std::cout << "After assignment(w/h):" << canvasWidth << " " << canvasHeight << std::endl;
    SDL_Texture* canvasTexture = SDL_CreateTexture(this->rend, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, canvasWidth, canvasHeight);
    SDL_SetRenderTarget(this->rend, canvasTexture);
    std::cout << "After Texture create" << std::endl;
    int xPos = 0;
    int yPos = 0;
    if (parent->key == ""){
        for(menuItem* child : parent->children) {
            std::cout << "X/Y:" << xPos << "/" << yPos << std::endl;
            std::cout << "X2/Y2:" << xPos + child->key.size() canvasHeight << "/" << yPos + canvasHeight << std::endl;
            //SDL_Rect *dstrect = new SDL_Rect{xPos,yPos,(xPos + child->key.size()),(yPos + canvasHeight)};
            SDL_Rect *dstrect = new SDL_Rect{xPos,yPos,(xPos + child->key.size()),14};
            xPos = xPos + child->key.size();
            int w;
            int h;
            SDL_QueryTexture(child->texture, NULL, NULL, &w, &h);
            std::cout << "W/H from texture:" << w << "/" << h << std::endl;
            SDL_RenderCopy(this->rend,child->texture, NULL, dstrect);
        }
    } else {
        std::cout << "In the childern loop, we shouldn't be here" << std::endl;
        for(menuItem* child : parent->children) {
            SDL_Rect *dstrect = new SDL_Rect {xPos,yPos, xPos + this->height, canvasWidth};
            xPos = xPos + this->height;
            SDL_RenderCopy(this->rend,child->texture, NULL, dstrect);
    
        }
    }
    SDL_SetRenderTarget(this->rend,NULL);
    return canvasTexture;
}

