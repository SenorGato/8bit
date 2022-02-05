#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Menu.h"


int main() {

    SDL_bool loopShouldStop = SDL_FALSE;
    SDL_Renderer *mRender = SDLisHard::init();
    
    TTF_Font *sans = TTF_OpenFont("/home/senoraraton/bins/8bit/assets/Sans.ttf", 12);
    
    if (sans == NULL) {std::cout << "Failed to load the font! SDL_ttf Error:" << TTF_GetError() << std::endl;}

    fontData *menuFont = new fontData({10,100,100}, sans, mRender);
    Menu *mainMenu = new Menu(menuFont,12,"blue");    
    mainMenu->font = menuFont;

    std::vector<std::string> topLevel = {"File", "Edit", "Help", "About"}; 
    std::vector<std::string> fileLevel = {"Open", "Save", "Save As"}; 
    std::vector<std::string> editLevel = {"F", "E", "H", "A"}; 
    std::vector<std::string> helpLevel = {"i", "d", "e", "b"}; 
    std::vector<std::string> aboutLevel = {"e", "t", "p", "t"}; 
    Menu::initMenu(topLevel, mainMenu ,mainMenu->head);
    Menu::initMenu(fileLevel,mainMenu, mainMenu->head->children.at(0));
    //initMenu(editLevel, mainMenu, mainMenu->head->sibling);
    //initMenu(helpLevel, mainMenu, mainMenu->head->sibling->sibling);
    //initMenu(aboutLevel, mainMenu, mainMenu->head->sibling->sibling);
    menuItem *query = Menu::fetchMenuItem("Save As", mainMenu->head);
    //std::cout << "Query->key:" << query->key << std::endl;    
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
