#include "init.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

int Init_Init() 
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_Log("Unable to init SDL: %s", SDL_GetError());
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("Unable to init SDL Image: %s", IMG_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("Unable to init SDL ttf: %s", TTF_GetError());
        return -1;
    }
    
    return 0;
}

void Init_Quit()
{
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}