#include "game.h"
#include "structs.h"
#include "piece.h"
#include "settings.h"
#include "board.h"
#include "stdbool.h"
#include "graphics.h"
#include "input.h"

void Game_loop(SDL_Renderer *renderer, Piece ***matrix)
{
    bool run = true;
    SDL_Event event;

    int i = 1;
    int j = 1;

    Move moves[64];
    int numberOfMoves = 0;


    while (run)
    {   
        // Input
        Input_handleGameQuit(&event, &run);
        Input_handleSelectPiece(&event, matrix, &i, &j);


        // Update
        SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};    
        numberOfMoves = Piece_getMoves(matrix, j, i, moves);

        // Drawing
        Graphics_clearScreen(renderer);

        Board_DrawBoard(renderer);
        Board_DisplayPieces(matrix, renderer);

        Graphics_drawRect(renderer, (SDL_Color){255, 0, 0, 255}, &rect);

        Game_drawSelectedPieceMoves(renderer, moves, numberOfMoves);

        Graphics_presentScreen(renderer);

        SDL_Delay(16);

    }
}


void Game_drawSelectedPieceMoves(SDL_Renderer *renderer, Move moves[], int numberOfMoves)
{
    for (int k = 0; k < numberOfMoves; k++)
    {   
        SDL_Rect drect = {moves[k].j * TILE_SIZE, moves[k].i * TILE_SIZE, TILE_SIZE, TILE_SIZE};    
        Graphics_fillRect(renderer, (SDL_Color){255, 0, 0, 255}, &drect);
    }
}