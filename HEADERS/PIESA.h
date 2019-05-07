/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */
#pragma once

#include <iostream>
#include <SDL.h>
#include <cstring>
#include "RENDERABLE.h"
#include "CLICKABLE.h"

class PIESA : public RENDERABLE, public CLICKABLE {

    SDL_Rect _Pos;
    bool _Clicked;
    char _TexturePath[ 100 ];


public :

    PIESA( SDL_Rect pos );
    PIESA (){}

    void SetPath( const char* str ) { strcpy( _TexturePath, str ); }
    SDL_Rect GetPos();
    void SetTexturePath( const char *str );
    void Reset();


    bool CheckPos ( int x, int y );
    bool RenderObject( SDL_Renderer * render, int xOffset, int yOffset );
    bool ClickAction( int x, int y );




};
