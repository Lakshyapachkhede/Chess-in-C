#include "game.h"
#include "structs.h"
#include "piece.h"
#include "settings.h"
#include "board.h"
#include "stdbool.h"
#include "graphics.h"

void Game_loop(SDL_Renderer *renderer, Piece ****matrix)
{
    bool run = true;
    SDL_Event event;
    while (run)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                run = false;
        }

        Graphics_clearScreen(renderer);
        Board_DrawBoard(renderer);


        Board_DisplayPieces(*matrix, renderer);

        Graphics_presentScreen(renderer);
        SDL_Delay(16);

    }
}