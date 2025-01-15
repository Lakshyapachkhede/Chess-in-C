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

    int i = -1;
    int j = -1;

    Move moves[64];
    int numberOfMoves = 0;

    bool pieceSelected = false;

    matrix[4][4] = Piece_createPiece(renderer, WHITE, ROOK);
    matrix[4][5] = Piece_createPiece(renderer, BLACK, BISHOP);

    while (run)
    {
        // Input
        Input_handleGameQuit(&event, &run);

        // TODO : i and j are used somewhere as rows or somewhere as columns
        // if it works dont touch it


        if (!pieceSelected)
        {
            pieceSelected = Input_handleSelectPiece(&event, matrix, &i, &j);
            if (pieceSelected)
            {
                numberOfMoves = Piece_getMoves(matrix, j, i, moves);
            }
        }
        else
        {
            Move *move = Input_getSelectTile(&event);

            if (move->i == j && move->j == i) // Deselecting the same piece
            {
                pieceSelected = false;
                i = -1;
                j = -1;
            }
            else if (move->i != -1) // Valid tile clicked
            {
                if (Game_checkValidMove(*move, moves, numberOfMoves))
                {
                    Game_movePiece(matrix, (Move){j, i}, *move);
                    pieceSelected = false;
                    i = -1;
                    j = -1;
                }
                else if (matrix[move->i][move->j] != NULL) // Clicked on another piece
                {
                    i = move->j;
                    j = move->i;
                    numberOfMoves = Piece_getMoves(matrix, j, i, moves);
                }
                else // Invalid move or empty square
                {
                    pieceSelected = false;
                    i = -1;
                    j = -1;
                }
            }
        }

        // Drawing
        Graphics_clearScreen(renderer);

        Board_DrawBoard(renderer);

        if (pieceSelected)
        {
            SDL_Rect rect = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            Graphics_fillRect(renderer, (SDL_Color)SELECT_COLOR, &rect);
            Game_drawSelectedPieceMoves(renderer, moves, numberOfMoves, matrix);
        }

        Board_DisplayPieces(matrix, renderer);

        Graphics_presentScreen(renderer);

        SDL_Delay(16);
    }
}

void Game_drawSelectedPieceMoves(SDL_Renderer *renderer, Move moves[], int numberOfMoves, Piece ***matrix)
{
    for (int k = 0; k < numberOfMoves; k++)
    {   
        SDL_Rect drect = {moves[k].j * TILE_SIZE, moves[k].i * TILE_SIZE, TILE_SIZE, TILE_SIZE};

        if (matrix[moves[k].i][moves[k].j] != NULL)
            Graphics_fillRect(renderer, (SDL_Color)CAPTURE_COLOR, &drect);
        else
            Graphics_fillRect(renderer, (SDL_Color)OPTIONS_COLOR, &drect);
    }
}

bool Game_checkValidMove(Move move, Move moves[], int numberOfMoves)
{
    for (int i = 0; i < numberOfMoves; i++)
    {
        if (moves[i].i == move.i && moves[i].j == move.j)
            return true;
    }

    return false;
}

void Game_movePiece(Piece ***matrix, Move startPlace, Move endPlace)
{
    matrix[endPlace.i][endPlace.j] = matrix[startPlace.i][startPlace.j];
    matrix[startPlace.i][startPlace.j] = NULL;
}
