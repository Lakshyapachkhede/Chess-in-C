#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"
#include <stdbool.h>
#include "structs.h"

void Input_handleGameQuit(SDL_Event *event, bool *run);
bool Input_handleSelectPiece(SDL_Event *event, Piece ***matrix, int *selectedI, int *selectedJ);
Move *Input_getSelectTile(SDL_Event *event);
#endif