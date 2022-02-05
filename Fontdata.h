#ifndef FONTDATA_H
#define FONTDATA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct fontData{
    SDL_Color textColor;
    TTF_Font* font;
    SDL_Renderer *renderer;
    int size;
    std::string path;

    fontData(std::string path, int size, SDL_Color textColor, SDL_Renderer *renderer){
        this->textColor = textColor;
        this->renderer = renderer;
        this->font = loadFont(path,size);
    }

    TTF_Font* loadFont(std::string path, int size) {
        TTF_Font *sans = TTF_OpenFont(path.c_str(), size);
        if (sans == NULL) {std::cout << "Failed to load the font! SDL_ttf Error:" << TTF_GetError() << std::endl;}
        return sans;
    }
};
#endif
