/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>

#include "RENDERABLE.h"
#include "GAME_ZONE.h"
#include "MENU.h"

class GAME : public RENDERABLE{

    SDL_Window* window;
    SDL_Renderer* render;
    SDL_Texture *background;
    int running;
    int _remiza;
    int _player_to_move;
    MENU meniu;
    MENU SetOption;
    MENU temporar;
    GAME ();

    static GAME* _instance;


public:

    GAME* GetInstance() {
        if ( _instance == NULL )
            _instance = new GAME;
        return _instance;
    }

    void Reset() {
        _player_to_move = 1;
        _remiza = 0;
        temporar.Clear();
    }

    int GetRemiza() { return _remiza; }
    int ProposeRemiza(  ) { _remiza = 1; }
    int AceptRemiza() { _remiza = 2; }
    int DeclineRemiza() { _remiza = 0;}
    void Quit() { running = 0; }
    void Logic();
    int ChangePlayerToMove( ) { _player_to_move = _player_to_move % 2 + 1; }
    bool RenderObject( SDL_Renderer *render, int xOffset, int yOffset);
    bool Action( int x, int y );
    bool Randare( );
    void Run();

};

#endif // GAME_H
