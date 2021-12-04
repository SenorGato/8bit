#include <SDL2/SDL.h>
#include <string>
#include <cstdio>
#include <stdio.h>
#include <iostream>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Map.h"
#include "Menu.h"

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
	SDL_FreeSurface( tile );
	tile = NULL;

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

bool loadMedia(std::string tileImage)
{
	//Load splash image
	std::string path = "./assets/" + tileImage;
	const char * c = path.c_str();
	tile = SDL_LoadBMP(c);
	if( tile == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "tile.bmp", SDL_GetError() );
	}
	return true;
}

int main (int argc, char* argv[]) {

    Map gamestate(800,800,10,10);
	std::string media = "whitetile2.bmp";

	if( !init(gamestate.width, gamestate.height) ) {
		printf( "Failed to load media!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia(media) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Apply the image
			
			SDL_Rect testRect;
			int tileSize = 32;
			testRect.x = tileSize * -1;
			testRect.y = tileSize * -1;
		
			for(int i = 0; i < (gamestate.width/tileSize); i++) {
				testRect.x = testRect.x + tileSize;
				testRect.y = tileSize * -1;
				for(int p = 0; p < (gamestate.height/tileSize); p++) {
					testRect.y = testRect.y + tileSize;
					SDL_BlitSurface( tile, NULL, gScreenSurface, &testRect);
				}
			}
			//Update the surface
			SDL_UpdateWindowSurface( gWindow );
			//Wait two seconds
			SDL_Delay( 2000 );
		}
	}
		
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	
	std::vector<std::string> keys {"1","2","3"};
	Menu test(gScreenSurface, keys, 32, gWindow);
	//SDL_UpdateWindowSurface(gWindow);
	SDL_Delay(2000);
	//Free resources and close SDL
	//close();
	return 0;
}
