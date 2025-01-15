#ifndef PIECE_H
#define PIECE_H

#include "structs.h"
#include "settings.h"

#define PIECE_SIZE TILE_SIZE

Piece *Piece_createPiece(SDL_Renderer *renderer, PieceColor color, Type type);
SDL_Texture *Piece_getImage(SDL_Renderer *renderer, PieceColor color, Type type);

int Piece_getMoves(Piece ***matrix, int i, int j, Move moves[]);

int Piece_getPawnMoves(Piece ***matrix, int i, int j, Move moves[]);
int Piece_getRookMoves(Piece ***matrix, int i, int j, Move moves[], int existingMoves);
int Piece_getBishopMoves(Piece ***matrix, int i, int j, Move moves[], int existingMoves);
int Piece_getQueenMoves(Piece ***matrix, int i, int j, Move moves[]);
int Piece_getKnightMoves(Piece ***matrix, int i, int j, Move moves[]);


#endif 