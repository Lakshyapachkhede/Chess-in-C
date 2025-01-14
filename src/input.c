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

bool Input_handleSelectPiece(SDL_Event *event, Piece ***matrix, int *selectedI, int *selectedJ)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {

        int x = event->button.x / PIECE_SIZE;
        int y = event->button.y / PIECE_SIZE;

        if (x == *selectedI && y == *selectedJ)
        {
            *selectedI = -1;
            *selectedJ = -1;
            return false;
        }
        else if (matrix[y][x] != NULL)
        {
            *selectedI = x;
            *selectedJ = y;
            return true;
        }
        else
        {
            *selectedI = -1;
            *selectedJ = -1;
            return false;
        }
    }
    return (*selectedI != -1 && *selectedJ != -1);
}

Move *Input_getSelectTile(SDL_Event *event)
{
    Move *move = (Move *)malloc(sizeof(Move));
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {

        int x = event->button.x / PIECE_SIZE;
        int y = event->button.y / PIECE_SIZE;

        move->i = y;
        move->j = x;

        return move;
    }
    else 
    {
        move->i = -1;
        move->j = -1;
    }
    return move;
}
