/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */

#include <iostream>
#include <SDL.h>

#include "MENU.h"

MENU :: MENU( SDL_Rect pos, std :: vector < std :: pair < std :: pair < SDL_Rect, void (*)() >  ,  char * > > states ) {

    _pos = pos;

    for ( int i = 0; i < states.size(); ++i ) {
        BUTTON aux( states[ i ].first.first, states[ i ].first.second, states[ i ].second );
        _Buttons.push_back( aux );
    }


}

void MENU :: AddButton( SDL_Rect pos, void(*funct)(), const char * text ) {

    BUTTON nou( pos, funct, text );
    _Buttons.push_back( nou );

}
bool MENU :: StergeButton( int index ) {

    if ( index >= _Buttons.size() )
        return false;

    _Buttons.erase(_Buttons.begin() + index, _Buttons.begin()+ index + 1 );

}

bool MENU :: CheckPos( int x, int y ) {
    if ( _pos.x <= x && x <= _pos.x + _pos.w ) {
        if ( _pos.y <= y && y <= _pos.y + _pos.h )
            return true;
    }
    return false;
}

bool MENU :: ClickAction( int x, int y ) {
    if ( !CheckPos( x, y ) )
        return false;

    int s = 0;
    for ( int i = 0; i < _Buttons.size(); ++i ){
        s += _Buttons[ i ].ClickAction( x, y );
    }

    return s;
}

bool MENU :: RenderObject( SDL_Renderer *render, int xOffset, int yOffset ){

    for ( int i = 0; i < _Buttons.size(); ++i ) {
        if ( !_Buttons[ i ].RenderObject( render, 0, 0 ) )
            return false ;
    }

    return true;

}

