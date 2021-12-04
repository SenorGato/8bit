#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include "Menu.h"

Menu::Menu(SDL_Surface* d, std::vector<std::string> k, int h) {
	std::vector<std::string> keys = k;
	std::cout << "(0):" << k.at(0) << " (2):" << k.at(2) << std::endl;
	buildMenu(d,h,k);
	}

SDL_Rect Menu::buildMenu(SDL_Surface* dest, int height, std::vector<std::string> k) {
	std::cout << "In buildMenu top" << std::endl;
	std::cout << "(0):" << k.at(0) << " (2):" << k.at(2) << std::endl;
	SDL_Rect menuRect;
	menuRect.x = 0;
	menuRect.y = 0;
	menuRect.w = dest->w;
	menuRect.h = height;
	
	std::string fullString = "";

	std::cout << "Key Size Out:"<< k.size() << std::endl;

	for(int i = 0; i < (k.size()); i++){
		std::cout << "Key Size In:"<< k.size() << std::endl;
		fullString = fullString + k.at(i);
		std::cout << fullString << std::endl;
	}
	const char * c = fullString.c_str();
	std::cout << "constString:" << *c << std::endl;
	std::cout << "fullString:" << fullString << std::endl;
	SDL_Texture* mTexture;
	SDL_Renderer* gRenderer = NULL;
	TTF_Font* sans = TTF_OpenFont("./assets/Sans.ttf", 12);
	SDL_Color textColor = {0,0,0};
	SDL_Surface* textSurface = TTF_RenderText_Solid(sans, c, textColor );
	SDL_BlitSurface(textSurface, NULL, dest, NULL);
	
 //Render some text in solid black to a hsurface
 //then blit to the upper left of the screen
 //then free the text surface
	SDL_Surface *screen;
	SDL_Color color={0,0,0};
	SDL_Surface *text_surface;
	if(!(text_surface=TTF_RenderText_Solid(sans,"Hello World!",color))) {
	//handle error here, perhaps print TTF_GetError at least
	} else {
		SDL_BlitSurface(text_surface,NULL,dest,NULL);
	//perhaps we can reuse it, but I assume not for simplicity.
		SDL_FreeSurface(text_surface);
	}
	std::cout << "Sans" << sans << " c" << c << std::endl;
	
	//if( textSurface == NULL )
	//{
	//    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	//}
	//else
	//{
		//Create texture from surface pixels
	//    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
	//    if( mTexture == NULL )
	//    {
	//        printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
	//    }
	//    else
	//    {
	//        std::cout << "This is a test string" << std::endl;
	//    }
	//
	//    //Get rid of old surface
	//    SDL_FreeSurface( textSurface );
	////}
	//return menuRect;
}

