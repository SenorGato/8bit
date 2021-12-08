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
void close();

bool loadMedia(std::string tileImage);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
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
	int tileSize = 32;

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
            testRect.x = tileSize * -1;
            testRect.y = tileSize * -1;
        
            for(int i = 0; i < (gamestate.width/tileSize); i++) {
                testRect.x = testRect.x + tileSize;
                testRect.y = tileSize * -1;
                for(int p = 0; p < (gamestate.height/tileSize); p++) {
                    testRect.y = testRect.y + tileSize;
                    //SDL_BlitSurface( tile, NULL, gScreenSurface, &testRect);
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
	
	//std::vector<std::string> keys {"1","2","3"};
    ////std::vector<SDL_Surface*> topbar;
    //Menu topbar = Menu(gScreenSurface, keys, tileSize);
    //std::cout << "Topbar:" << &topbar << std::endl;
    //SDL_Surface* menuSurface = topbar.menuSurface; 
    //std::cout << "MenuSurface:" << &menuSurface << std::endl;
    
    
    SDL_Texture* mTexture;
    SDL_Renderer* gRenderer = NULL;
    //gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); 
    TTF_Font* sans = TTF_OpenFont("./assets/Sans.ttf",12);
    SDL_Color textColor = {0,0,0};
    //SDL_Surface* textSurface = TTF_RenderText_Solid(sans, "This is a test",textColor);
    //mTexture = SDL_CreateTextureFromSurface(gRenderer,textSurface);
    //SDL_FreeSurface(textSurface);

    
    
    
    
    SDL_BlitSurface(tile, NULL, gScreenSurface, NULL);
    SDL_UpdateWindowSurface( gWindow );
    SDL_Delay(2000);
    //Free resources and close SDL
    close();
	return 0;
}
