#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>

struct menuItem {
    menuItem* parent;
    menuItem* sibling;
    std::vector<menuItem*> children;
    std::string key;
    SDL_Texture* renderedSurface;
    
    menuItem(){};
    menuItem(menuItem* parent, menuItem* sibling, std::string key) {
        this->parent = parent;
        this->sibling = sibling;
        this->key = key;
    };
};

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

class Menu {
    public:
    menuItem *head;
    fontData *font;
    int height;
    std::string backgroundColor;
};

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

SDL_Texture* renderText(std::string key, fontData *data) {
    //I should free the texture here first
    SDL_Surface* textSurface = TTF_RenderText_Solid(data->font,key.c_str(), data->textColor); 
    if(textSurface == NULL) {
        std::cout << "Unable to render text surface! SDL_ttf Error:" << TTF_GetError() << std::endl;
    } else {
        SDL_Texture* mTexture = SDL_CreateTextureFromSurface(data->renderer, textSurface);
        if(mTexture == NULL) {
            std::cout << "Unable to create from rendered text! SDL Error:" << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(textSurface);
    return mTexture;
    }
    return NULL;
}

void initMenu(std::vector<std::string> keys, Menu *menu, menuItem* parent = new menuItem()){
    menuItem* sib = new menuItem();
    for(std::string key : keys) {
        std::cout << "Now your in the children loop.  Key:" << key << std::endl;
        parent->children.push_back (new menuItem{parent, sib, key});
        parent->children.back()->renderedSurface = renderText(key,menu->font);
        sib = parent->children.back();
        std::cout << "end of child for, test assign:" << parent->children.back()->key << std::endl;
    }
}

int main() {

    SDL_bool loopShouldStop = SDL_FALSE;
    SDL_Renderer *mRender = init();
    
    TTF_Font *sans = TTF_OpenFont("/home/senoraraton/bins/8bit/assets/Sans.ttf", 12);
    
    if (sans == NULL) {std::cout << "Failed to load the font! SDL_ttf Error:" << TTF_GetError() << std::endl;}

    fontData *menuFont = new fontData({10,100,100}, sans, mRender);
    Menu *mainMenu = new Menu();    
    mainMenu->font = menuFont;

    std::vector<std::string> topLevel = {"File", "Edit", "Help", "About"}; 
    std::vector<std::string> fileLevel = {"Open", "Save", "Save As"}; 
    std::vector<std::string> editLevel = {"F", "E", "H", "A"}; 
    std::vector<std::string> helpLevel = {"i", "d", "e", "b"}; 
    std::vector<std::string> aboutLevel = {"e", "t", "p", "t"}; 
    initMenu(topLevel,mainMenu);
    initMenu(fileLevel,menuFont, mainMenu->head);
    initMenu(editLevel, menuFont, mainMenu->head->sibling);
    initMenu(helpLevel, menuFont, mainMenu->head->sibling->sibling);
    initMenu(aboutLevel, menuFont, mainMenu->head->sibling->sibling);
    
    SDL_Texture *mTex = renderText("Testing",menuFont);
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
