#include "piece.h"
#include "graphics.h"
#include "stdio.h"
Piece *Piece_createPiece(SDL_Renderer *renderer, PieceColor color, Type type)
{
    Piece *piece = (Piece*)malloc(sizeof(Piece));
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