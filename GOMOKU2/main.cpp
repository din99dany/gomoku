/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 * SDL SI SDL_TTF VARIANTA 64 BITS
 * A SE IGNORA CE SCRIE IN FEREASTA DE RULARE
 */
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

#include "../HEADERS/GAME.h"

int main( int argc, char **argv ) {

    SDL_Init(  SDL_INIT_EVERYTHING );

    if ( TTF_Init() == -1 ) {
        std :: cout << TTF_GetError();
        return 0;
    }

    GAME *Da = Da ->GetInstance();
    Da->Run();

}
