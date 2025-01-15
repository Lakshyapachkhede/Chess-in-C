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
        case ROOK:
            return Piece_getRookMoves(matrix, i, j, moves, 0);
        case BISHOP:
            return Piece_getBishopMoves(matrix, i, j, moves, 0);
        case QUEEN:
            return Piece_getQueenMoves(matrix, i, j, moves);
        case KNIGHT:
            return Piece_getKnightMoves(matrix, i, j, moves);
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

    if ((piece->color == WHITE && i == 0) || (piece->color == BLACK && i == 7))
    {
        SDL_Log("Implement pawn promotion");
        return 0; // Todo implement pawn promotion
    }
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

        if (matrix[i + 2 * direction][j] == NULL && matrix[i + direction][j] == NULL)
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

static int Piece_getLinearMoves(Piece ***matrix, int i, int j, int di, int dj, PieceColor color, Move moves[], int moveCount)
{
    int tempi = i + di;
    int tempj = j + dj;

    while (tempi >= 0 && tempi < ROWS &&
           tempj >= 0 && tempj < COLS &&
           matrix[tempi][tempj] == NULL)
    {
        moves[moveCount++] = (Move){tempi, tempj};
        tempi += di;
        tempj += dj;
    }

    if (tempi >= 0 && tempi < ROWS &&
        tempj >= 0 && tempj < COLS &&
        matrix[tempi][tempj]->color != color)
    {
        moves[moveCount++] = (Move){tempi, tempj};
    }

    return moveCount;
}

int Piece_getRookMoves(Piece ***matrix, int i, int j, Move moves[], int existingMoves)
{
    int moveCount = existingMoves;
    Piece *piece = matrix[i][j];

    // left
    moveCount = Piece_getLinearMoves(matrix, i, j, 0, -1, piece->color, moves, moveCount);

    // right
    moveCount = Piece_getLinearMoves(matrix, i, j, 0, 1, piece->color, moves, moveCount);

    // up
    moveCount = Piece_getLinearMoves(matrix, i, j, -1, 0, piece->color, moves, moveCount);

    // down
    moveCount = Piece_getLinearMoves(matrix, i, j, 1, 0, piece->color, moves, moveCount);

    return moveCount;
}

int Piece_getBishopMoves(Piece ***matrix, int i, int j, Move moves[], int existingMoves)
{
    int moveCount = existingMoves;
    Piece *piece = matrix[i][j];

    // up - left
    moveCount = Piece_getLinearMoves(matrix, i, j, -1, -1, piece->color, moves, moveCount);

    // up - right
    moveCount = Piece_getLinearMoves(matrix, i, j, -1, 1, piece->color, moves, moveCount);

    // down - left
    moveCount = Piece_getLinearMoves(matrix, i, j, 1, -1, piece->color, moves, moveCount);

    // down - right
    moveCount = Piece_getLinearMoves(matrix, i, j, 1, 1, piece->color, moves, moveCount);

    return moveCount;
}

int Piece_getQueenMoves(Piece ***matrix, int i, int j, Move moves[])
{
    int moveCount = 0;

    // diagonal moves
    moveCount = Piece_getBishopMoves(matrix, i, j, moves, moveCount);

    // linear moves
    moveCount = Piece_getRookMoves(matrix, i, j, moves, moveCount);

    return moveCount;
}

int Piece_getKnightMoves(Piece ***matrix, int i, int j, Move moves[])
{
    int moveCount = 0;
    Piece *piece = matrix[i][j];

    int possibleMoves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for (int k = 0; k < 8; k++)
    {
        int tempi = i + possibleMoves[k][0];
        int tempj = j + possibleMoves[k][1];

        if (tempi >= 0 && tempi < ROWS && tempj >= 0 && tempj < COLS)
        {
            if (matrix[tempi][tempj] == NULL || matrix[tempi][tempj]->color != piece->color)
            {
                moves[moveCount++] = (Move){tempi, tempj};
            }
        }
    }

    return moveCount;
}
