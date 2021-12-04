#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Menu.h"

Menu::Menu(SDL_Surface* d, std::vector<std::string> k, int h) {
	std::vector<std::string> keys = k;
	buildMenu(d,h);
	}

SDL_Rect Menu::buildMenu(SDL_Surface* dest, int height) {
	SDL_Rect menuRect;
	menuRect.x = 0;
	menuRect.y = 0;
	menuRect.w = dest->w;
	menuRect.h = height;
	
	std::string fullString = NULL;
	for(int i = 0; i < keys.size(); i++){
		fullString = fullString + keys.at(i);
		std::cout << fullString << std::endl;
	}
	const char * c = fullString.c_str();
	
	SDL_Texture* mTexture;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* sans = TTF_OpenFont("Sans.ttf", 12);
	SDL_Color textColor = {0,0,0};
    SDL_Surface* textSurface = TTF_RenderText_Solid(sans, c, textColor );
    
	if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
			std::cout << "This is a test string" << std::endl;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

