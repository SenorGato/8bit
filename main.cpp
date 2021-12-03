#include <SDL2/SDL.h>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <string>
#include "Map.h"

//string assets = './assets';
//SDL Init

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(std::string tileImage);

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* blacktile = NULL;
SDL_Surface* whitetile = NULL;
SDL_Surface* tile = NULL;

bool init(int x, int y)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, x, y, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

	return success;
}

void close()
{
	//Deallocate surface
	//SDL_FreeSurface( tile );
	//tile = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool loadMedia(std::string tileImage)
{
	//Loading success flag
	bool success = true;

	//Load splash image
	std::string path = "./assets/" + tileImage;
	const char * c = path.c_str();
	tile = SDL_LoadBMP(c);
	if( tile == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "tile.bmp", SDL_GetError() );
		success = false;
	}

	return success;
}

int main (int argc, char* argv[]) {

    Map gamestate(800,800,10,10);

    for(int i = 0; i < gamestate.grid.size(); i++) {
        if (i%2) {
            gamestate.grid.at(i).sprite = "1";
        } else {
            gamestate.grid.at(i).sprite= "2";
    	}
	}

	if( !init(gamestate.width, gamestate.height) ) {
		printf( "Failed to load media!\n" );
	}
	else
	{
		//Load media
		std::string media = "blacktiletiny.bmp";
		if( !loadMedia(media) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Apply the image
			
			SDL_Rect testRect;
			testRect.x = 100;
			testRect.y = 100;

			SDL_BlitSurface( tile, NULL, gScreenSurface, &testRect);
			
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );

			//Wait two seconds
			SDL_Delay( 8000 );
		}
	}

	//Free resources and close SDL
	close();
}
