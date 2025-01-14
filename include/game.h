#ifndef GAME_H
#define GAME_H
#include "settings.h"
#include "structs.h"
#include "SDL2/SDL.h"
#include "stdbool.h"

void Game_loop(SDL_Renderer *renderer, Piece ***matrix);
void Game_drawSelectedPieceMoves(SDL_Renderer *renderer, Move moves[], int numberOfMoves);
bool Game_checkValidMove(Move move, Move moves[], int numberOfMoves);
void Game_movePiece(Piece ***matrix, Move startPlace, Move endPlace);
#endif


