#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <SDL.h>

/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */

#include "CLICKABLE.h"
#include "RENDERABLE.h"
#include "BUTTON.h"

class MENU : public CLICKABLE, public RENDERABLE {

    SDL_Rect _pos;
    std :: vector < BUTTON > _Buttons;

public:
    MENU( SDL_Rect pos, std :: vector < std :: pair < std :: pair < SDL_Rect, void (*)() >  ,  char * > > states );
    MENU (){}

    void Clear() {
        while ( _Buttons.size() != 0 ) {
            StergeButton( 0 );
        }
    }
    void AddButton( SDL_Rect, void(*)(), const char * );
    bool StergeButton( int number );
    int GetSize() { return _Buttons.size(); }
    bool CheckPos( int x, int y );
    bool ClickAction( int x, int y );
    bool RenderObject( SDL_Renderer *render, int xOffset, int yOffset );





};


#endif // MENU_H
