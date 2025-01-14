#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "SDL2/SDL.h"

int Graphics_GetWindowRenderer(SDL_Window **window, SDL_Renderer **renderer);
void Graphics_FreeWindowRenderer(SDL_Window *window, SDL_Renderer *renderer);

void Graphics_clearScreen(SDL_Renderer *renderer);
void Graphics_renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect);
void Graphics_presentScreen(SDL_Renderer *renderer);
SDL_Texture *Graphics_getTextureFromPath(SDL_Renderer *renderer, char *path);

void Graphics_drawRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect *rect);
void Graphics_fillRect(SDL_Renderer *renderer, SDL_Color color, SDL_Rect *rect);

#endif // GRAPHICS_H
