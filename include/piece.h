#ifndef PIECE_H
#define PIECE_H

#include "structs.h"

#define PIECE_SIZE TILE_SIZE

Piece *Piece_createPiece(SDL_Renderer *renderer, PieceColor color, Type type);
SDL_Texture *Piece_getImage(SDL_Renderer *renderer, PieceColor color, Type type);





#endif 