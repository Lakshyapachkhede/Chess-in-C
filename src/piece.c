#include "piece.h"
#include "graphics.h"
#include "settings.h"
#include "stdio.h"

Piece *Piece_createPiece(SDL_Renderer *renderer, PieceColor color, Type type)
{
    Piece *piece = (Piece *)malloc(sizeof(Piece));
    piece->color = color;
    piece->type = type;
    piece->img = Piece_getImage(renderer, color, type);

    return piece;
}

SDL_Texture *Piece_getImage(SDL_Renderer *renderer, PieceColor color, Type type)
{
    if (type == EMPTY)
        return NULL;

    char path[64];
    sprintf(path, "../assets/images/%d%d.png", color, type);
    SDL_Texture *texture = Graphics_getTextureFromPath(renderer, path);
    return texture;
}

int Piece_getMoves(Piece ***matrix, int i, int j, Move moves[])
{
    if (!(i < 0 || i >= ROWS || j < 0 || j >= COLS))
    {
        switch (matrix[i][j]->type)
        {
        case PAWN:
            return Piece_getPawnMoves(matrix, i, j, moves);
            break;

        default:
            break;
        }
    }
    return 0;
}

int Piece_getPawnMoves(Piece ***matrix, int i, int j, Move moves[])
{

    int moveCount = 0;
    Piece *piece = matrix[i][j];

    int direction = (piece->color == WHITE) ? -1 : 1;

    // One Step
    if (i + direction >= 0 &&
        i + direction < ROWS &&
        matrix[i + direction][j] == NULL)
    {
        moves[moveCount++] = (Move){i + direction, j};
    }

    // First Move Two Step
    if ((piece->color == WHITE && i == 6) ||
        (piece->color == BLACK && i == 1))
    {

        if (matrix[i + 2 * direction][j] == NULL)
            moves[moveCount++] = (Move){i + 2 * direction, j};
    }

    // Capture Diagonally left
    if (j > 0 && matrix[i + direction][j - 1] != NULL &&
        matrix[i + direction][j - 1]->color != piece->color)
    {
        moves[moveCount++] = (Move){i + direction, j - 1};
    }

    // Capture Diagonally right
    if (j < COLS - 1 && matrix[i + direction][j + 1] != NULL &&
        matrix[i + direction][j + 1]->color != piece->color)
    {
        moves[moveCount++] = (Move){i + direction, j + 1};
    }

    return moveCount;
}