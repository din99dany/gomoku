/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */
#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <SDL.h>
#include "CLICKABLE.h"
#include "RENDERABLE.h"

class BUTTON : public CLICKABLE, public RENDERABLE {

    SDL_Rect _pos;
    void (*_action_pointer)();
    char _text[ 100 ];

public:

    BUTTON ( SDL_Rect pos, void (*action_pointer)(), const char* str );

    bool CheckPos( int x, int y );

    bool ClickAction( int x, int y );
    bool RenderObject( SDL_Renderer* render, int xOffset, int yOffset );



};

#endif
