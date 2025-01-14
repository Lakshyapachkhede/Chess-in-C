#ifndef STRUCTS_H
#define STRUCTS_H

#include <SDL2/SDL.h>

typedef enum
{
    WHITE,
    BLACK
} PieceColor;

typedef enum
{
    EMPTY,
    PAWN,
    ROOK,
    BISHOP,
    KNIGHT,
    QUEEN,
    KING
} Type;

typedef struct
{
    PieceColor color;
    Type type;
    SDL_Texture *img;
} Piece;

#endif