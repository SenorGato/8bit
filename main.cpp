#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Menu.h"
#include "SDLisHard.h"
//Consider implementing color class: https://stackoverflow.com/questions/39662339/what-is-a-good-way-to-store-color

int main() {

    SDL_Renderer *mRender = SDLisHard::init();
    SDL_bool loopShouldStop = SDL_FALSE;
    
    fontData *menuFont = new fontData("/home/senoraraton/bins/8bit/assets/Sans.ttf",12,{10,100,100}, mRender);
    Menu *mainMenu = new Menu(menuFont, 20, std::vector<int> {255,255,255});    
    std::cout << "MainMenu Test: " << mainMenu->head << std::endl;
    std::vector<std::string> topLevel = {"File", "Edit", "Help", "About"}; 
    std::vector<std::string> fileLevel = {"Open", "Save", "Save As"}; 
    std::vector<std::string> editLevel = {"F", "E", "H", "A"}; 
    std::vector<std::string> helpLevel = {"i", "d", "e", "b"}; 
    std::vector<std::string> aboutLevel = {"e", "t", "p", "t"}; 
    Menu::initMenu(topLevel, mainMenu ,mainMenu->head);
    Menu::initMenu(fileLevel,mainMenu, mainMenu->head->children.at(0));
    std::cout << "Main Menu Children:" << mainMenu->head->children.at(1)->key << std::endl;
    //initMenu(editLevel, mainMenu, mainMenu->head->sibling);
    //initMenu(helpLevel, mainMenu, mainMenu->head->sibling->sibling);
    //initMenu(aboutLevel, mainMenu, mainMenu->head->sibling->sibling);
    menuItem *q = Menu::fetchMenuItem("Save As", mainMenu->head);
    std::cout << "Q->key:" << q->key << std::endl;    
    SDL_Texture *mTex = SDLisHard::renderText("Testing",menuFont);
    SDL_Rect *dstrect = new SDL_Rect {0,0,100,100};
    
    while (!loopShouldStop) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    loopShouldStop = SDL_TRUE;
                    break;
            }
        }
        SDL_RenderClear(mRender);
        SDL_RenderCopy(mRender,mTex, NULL, dstrect);
        SDL_RenderPresent(mRender);
    }
}
