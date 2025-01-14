#include "SDL2/SDL.h"
#include "init.h"
#include "graphics.h"
#include "structs.h"
#include "settings.h"
#include "board.h"
#include "game.h"

int main(int argc, char *argv[])
{   

    // initialising

    if (Init_Init() == -1) {
        exit(1);
    }

    SDL_Window *window;
    SDL_Renderer *renderer;

    if (Graphics_GetWindowRenderer(&window, &renderer) == -1)  {
        exit(1);
    }

    Piece ***matrix = Board_initBoard(renderer);


    // game loop
    Game_loop(renderer, matrix);

    // freeing up resources
    Board_freeBoard(matrix);
    Graphics_FreeWindowRenderer(window, renderer);
    Init_Quit();

    
    
    return 0;
}
