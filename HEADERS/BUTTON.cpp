/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */
#include <iostream>
#include <cstring>
#include <SDL.h>
#include <SDL_ttf.h>
#include "BUTTON.h"


BUTTON  :: BUTTON ( SDL_Rect pos, void (*action_pointer)(), const char* str ) {

    _pos = pos;
    _action_pointer = action_pointer;

    strcpy( _text, str );

}

bool BUTTON :: CheckPos( int x, int y ) {

    if ( _pos.x <= x && x <= _pos.x + _pos.w ) {
        if ( _pos.y <= y && y <= _pos.y + _pos.h )
            return true;
    }

    return false;

}

bool BUTTON :: ClickAction( int x, int y ) {

    if ( !CheckPos( x, y ) )
        return false;


    _action_pointer();

    return  true;

}

bool BUTTON :: RenderObject( SDL_Renderer* render, int xOffset, int yOffset ) {

    TTF_Font *font = TTF_OpenFont( "../fonts/tnr.ttf", 100 );
    SDL_Surface *surface_text = TTF_RenderText_Blended( font, _text, {0,0,0}  );
    SDL_Texture * surface = SDL_CreateTextureFromSurface( render, surface_text );

    SDL_SetRenderDrawColor( render, 125, 125, 125, 0 );
    SDL_RenderFillRect( render, &_pos );
    SDL_RenderDrawRect( render, &_pos );
    SDL_SetRenderDrawColor( render, 255, 255, 255, 0 );

    SDL_RenderCopy( render, surface, NULL, &_pos );


    return true;


}

