#ifndef FONTDATA_H
#define FONTDATA_H
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct fontData{
    SDL_Color textColor;
    TTF_Font* font;
    SDL_Renderer *renderer;
    fontData(SDL_Color textColor,TTF_Font* font,SDL_Renderer *renderer){
        this->textColor = textColor;
        this->font = font;
        this->renderer = renderer;
    }
};
