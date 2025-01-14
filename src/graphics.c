#include "graphics.h"
#include "SDL2/SDL_image.h"
#include "settings.h"

int Graphics_GetWindowRenderer(SDL_Window **window, SDL_Renderer **renderer)
{
    *window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

void Graphics_FreeWindowRenderer(SDL_Window *window, SDL_Renderer *renderer)
{
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }

    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
}

void Graphics_clearScreen(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics_renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect)
{
    SDL_RenderCopy(renderer, texture, NULL, rect);
}

void Graphics_presentScreen(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}

SDL_Texture *Graphics_getTextureFromPath(SDL_Renderer *renderer, char *path)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, path);
    if (!texture)
    {
        SDL_Log("Unable to load texture: %s", IMG_GetError());
        return NULL;
    }

    return texture;
}

