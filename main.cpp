#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct menuItem {
    menuItem* parent;
    menuItem* sibling;
    std::vector<menuItem*> children;
    std::string key;
    SDL_Surface* renderedSurface;
    
    menuItem(){};
    menuItem(menuItem* parent){};
    menuItem(menuItem* parent, menuItem* sibling) {
        this->parent = parent;
        this ->sibling = sibling;
    };
};

struct fontData{
    SDL_Color textColor;
    TTF_Font* font;
    SDL_Renderer *renderer;
    fontData(SDL_Color textColor, TTF_Font* font, SDL_Renderer *renderer){
        this->textColor = textColor;
        this->font = font;
        this ->renderer = renderer;
    };
};

std::vector<menuItem> mainMenu;
    
//Build a struct that holds all this data, init struct in main() pass struct to initMenu
void initMenu(std::vector<std::string> keys, menuItem* parent = NULL){
    menuItem* sib = new menuItem();
    if (parent == NULL) {
        for (std::string key : keys){
            mainMenu.push_back (new menuItem{parent, sib});
            mainMenu.back().key = key;
            sib = &mainMenu.back();
            //mainMenu.back().renderedSurface = renderText(key, )
        }
    } else {
        for(std::string key : keys) {
            parent->children.push_back (new menuItem{parent, sib});
            parent->children.back()->key = key;
            sib = parent->children.back();
        }
    }
}

SDL_Renderer* init(){

    SDL_Window *win = NULL;
    SDL_Renderer *renderer = NULL;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not init! SDL_Error:" << SDL_GetError() << std::endl;
    } else {
        win = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_SHOWN);        
        if (win == NULL) {
            std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        }
    }
    
    if(TTF_Init() == -1) {
        std::cout << "SDF_ttf could not initalize! SDL_ttf Error:" << TTF_GetError() << std::endl;
    }
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
} 

SDL_Texture* renderText(std::string key, SDL_Color textColor, TTF_Font* font, SDL_Renderer *renderer) {
    //I should free the texture here first
    SDL_Surface* textSurface = TTF_RenderText_Solid(font,key.c_str(), textColor); 
    if(textSurface == NULL) {
        std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError() << std::endl;
    } else {
        SDL_Texture* mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(mTexture == NULL) {
            std::cout << "Unable to create from rendered text! SDL Error:" << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(textSurface);
    return mTexture;
    }
}

int main() {
    std::vector<std::string> topLevel = {"File", "Edit", "Help", "About"}; 
    std::vector<std::string> fileLevel = {"File", "Edit", "Help", "About"}; 
    std::vector<std::string> editLevel = {"File", "Edit", "Help", "About"}; 
    std::vector<std::string> helpLevel = {"File", "Edit", "Help", "About"}; 
    std::vector<std::string> aboutLevel = {"File", "Edit", "Help", "About"}; 
    initMenu(topLevel);
    initMenu(fileLevel, &mainMenu.at(0));
    initMenu(editLevel, &mainMenu.at(1));
    initMenu(helpLevel, &mainMenu.at(2));
    initMenu(aboutLevel, &mainMenu.at(3));

    SDL_bool loopShouldStop = SDL_FALSE;
    SDL_Renderer *mRender = init();
    SDL_Color textColor = {100,10,10};
    
    TTF_Font *sans = TTF_OpenFont("/home/senoraraton/bins/8bit/assets/Sans.ttf", 12);
    if (sans == NULL) {
        std::cout << "Failed to load the font! SDL_ttf Error:" << TTF_GetError() << std::endl;
    }

    SDL_Texture *mTex = renderText("Testing",textColor, sans, mRender);
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
