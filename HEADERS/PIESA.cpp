/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */
#include <iostream>
#include <SDL.h>
#include <cstring>

#include "PIESA.h"

PIESA :: PIESA( SDL_Rect pos ) {

    _Pos = pos;
    _Clicked = false;
}


bool PIESA :: CheckPos ( int x, int y ) {

    if ( _Pos.x <= x && x <= _Pos.x + _Pos.w )
        if ( _Pos.y <= y && y <= _Pos.y + _Pos.h )
            return 1;

    return 0;

}

void PIESA :: Reset () {

    _TexturePath[ 0 ] = '\0';
    _Clicked = 0;

}

bool PIESA :: ClickAction ( int x, int y ) {

    if ( CheckPos( x, y ) ) {
        _Clicked = true;
        return 1;
    }

    return 0;

}

bool PIESA :: RenderObject( SDL_Renderer * render, int xOffset, int yOffset ) {

    if (  !_Clicked ) return 0;

    SDL_Surface *surface = SDL_LoadBMP(  _TexturePath );
    if ( surface == NULL ) {
        std :: cout << "Cant load piece surface.\n";
        return 0;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface( render, surface );
    if ( texture == NULL ) {
        std :: cout << "Cant load piece texture.\n";
        std :: cout << _TexturePath << "\n";
        return 0;
    }

    SDL_Rect pos = (SDL_Rect) { _Pos.x + xOffset, _Pos.y + yOffset, _Pos.w, _Pos.h };
    SDL_RenderCopy( render, texture, NULL, &pos );

    SDL_FreeSurface ( surface );
    SDL_DestroyTexture ( texture );

    return 1;

}

SDL_Rect PIESA :: GetPos ( ) {
    return _Pos;
}


void PIESA :: SetTexturePath( const char *str ) {
    strcpy( _TexturePath, str );
}
