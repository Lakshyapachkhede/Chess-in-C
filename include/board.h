#ifndef BOARD_H
#define BOARD_H

#include "settings.h"
#include "SDL2/SDL.h"
#include "structs.h"


void Board_DrawBoard(SDL_Renderer *renderer);
void Board_DisplayPieces(Piece ***board, SDL_Renderer *renderer);
Piece ***Board_initBoard(SDL_Renderer *renderer);
void Board_freeBoard(Piece ***matrix);

#endif