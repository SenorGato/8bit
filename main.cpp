
#include <iostream>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Menu.h"
//Consider implementing color class: https://stackoverflow.com/questions/39662339/what-is-a-good-way-to-store-color

int main() {

    SDLisHard::winInfo winInfo = SDLisHard::init();
    std::cout << "winInfo:window:" << winInfo.win << " renderer:" << winInfo.renderer << std::endl;
    SDL_bool loopShouldStop = SDL_FALSE;
    

//  Main Menu init:

    fontData *menuFont = new fontData("/home/senoraraton/bins/8bit/assets/Sans.ttf",12,{10,100,100}, winInfo.renderer);
    Menu *mainMenu = new Menu(menuFont, 20, std::vector<int> {255,255,255});    

    mainMenu->initMenu({"File", "Edit", "Help", "About"}, mainMenu->head);
    mainMenu->initMenu({"Open", "Save", "Save As"},  mainMenu->fetchMenuItem("File", mainMenu->head));
    mainMenu->initMenu({"F", "E", "H", "A"}, mainMenu->fetchMenuItem("Edit", mainMenu->head));
    mainMenu->initMenu({"i", "d", "e", "b"}, mainMenu->fetchMenuItem("Help", mainMenu->head));
    mainMenu->initMenu({"x", "t", "p", "t"}, mainMenu->fetchMenuItem("About", mainMenu->head));
    //mainMenu->renderMenu(mainMenu->head);
    std::cout << "X:" << mainMenu->fetchMenuItem("About", mainMenu->head)->key << std::endl;

    SDL_Texture *mTex = SDLisHard::renderText("Testing",menuFont);
    SDL_Rect *dstrect = new SDL_Rect {0,0,100,100};
    std::cout << "Renderer check:" << winInfo.renderer << std::endl;
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
        SDL_RenderClear(winInfo.renderer);
        SDL_RenderCopy(winInfo.renderer,mTex, NULL, dstrect);
        SDL_RenderPresent(winInfo.renderer);
    }
}
