#ifndef SDLISHARD_H
#define SDLISHARD_H

#include <utility>
#include "Fontdata.h"

namespace SDLisHard {

struct winInfo{
    SDL_Window* win;
    SDL_Renderer* renderer;
};


    inline winInfo init(){ 
        SDL_Window* win = nullptr;
        SDL_Renderer* renderer = nullptr;
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not init! SDL_Error:" << SDL_GetError() << std::endl;
        } else {

            if(TTF_Init() == -1) {
                std::cout << "SDF_ttf could not initalize! SDL_ttf Error:" << TTF_GetError() << std::endl;
            } else {
               win = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);        
                if (win == NULL) {
                    std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
                } else {
                    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
                    std::cout << "In SDLisHard, renderer:" << renderer << std::endl;
                    if (renderer = NULL) {
                        std::cout << "Renderer could not be created! SDL_Error:" << SDL_GetError() << std::endl;
                    }
                }
            }
        }
        return winInfo{win,renderer};
    }

    inline SDL_Texture* renderText(std::string key, fontData *font) {
        //I should free the texture here first
        SDL_Surface* textSurface = TTF_RenderText_Solid(font->font,key.c_str(), font->textColor); 
        if(textSurface == NULL) {
            std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError() << std::endl;
        } else {
            SDL_Texture* mTexture = SDL_CreateTextureFromSurface(font->renderer, textSurface);
            if(mTexture == NULL) {
                std::cout << "Unable to create from rendered text! SDL Error:" << SDL_GetError() << std::endl;
            }
            SDL_FreeSurface(textSurface);
        return mTexture;
        }
        return NULL;
    }
}
#endif
