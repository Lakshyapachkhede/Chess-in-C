#include "SDL2/SDL.h"
#include "board.h"
#include "graphics.h"
#include "structs.h"
#include "settings.h"
#include "piece.h"
#include <stdio.h>

void Board_DrawBoard(SDL_Renderer *renderer)
{

    SDL_Color light_color = {234, 232, 210, 255};
    SDL_Color dark_color = {75, 114, 152, 255};
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            SDL_Rect rect = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if ((i + j) % 2 == 0)
            {
                SDL_SetRenderDrawColor(renderer, light_color.r, light_color.g, light_color.b, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, dark_color.r, dark_color.g, dark_color.b, 255);
            }
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}

void Board_DisplayPieces(Piece ***board, SDL_Renderer *renderer)
{

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] && board[i][j]->type != EMPTY)
            {
                SDL_Rect rect = {j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
                Graphics_renderTexture(renderer, board[i][j]->img, &rect);
            }
        }
    }

}

Piece ***Board_initBoard(SDL_Renderer *renderer)
{
    Piece ***matrix = (Piece ***)malloc(ROWS * sizeof(Piece **));
    for (int i = 0; i < ROWS; i++)
    {
        matrix[i] = (Piece **)malloc(COLS * sizeof(Piece *));
        for (int j = 0; j < COLS; j++)
        {
            matrix[i][j] = NULL;
        }
    }

    for (int j = 0; j < COLS; j++)
    {
        matrix[1][j] = Piece_createPiece(renderer, BLACK, PAWN);
        matrix[6][j] = Piece_createPiece(renderer, WHITE, PAWN);
    }

    Type pieces[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};

    for (int j = 0; j < COLS; j++)
    {
        matrix[0][j] = Piece_createPiece(renderer, BLACK, pieces[j]);
        matrix[7][j] = Piece_createPiece(renderer, WHITE, pieces[j]);
    }

    return matrix;
}

void Board_freeBoard(Piece ***matrix)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (matrix[i][j] != NULL)
            {
                free(matrix[i][j]); // Free each piece
            }
        }
        free(matrix[i]); // Free each row
    }
    free(matrix); // Free the matrix
}
