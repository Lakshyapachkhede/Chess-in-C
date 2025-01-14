#include "input.h"
#include "piece.h"
#include "settings.h"

void Input_handleGameQuit(SDL_Event *event, bool *run)
{
    if (SDL_PollEvent(event))
    {
        if (event->type == SDL_QUIT)
            *run = false;
    }
}

void Input_handleSelectPiece(SDL_Event *event, Piece ***matrix, int *selectedI, int *selectedJ)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {

        int x = event->button.x / PIECE_SIZE;
        int y = event->button.y / PIECE_SIZE;

        if (matrix[y][x] != NULL)
        {
            *selectedI = x;
            *selectedJ = y;
        }
        else
        {
            *selectedI = -1;
            *selectedJ = -1;
        }
    }
}