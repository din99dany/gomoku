/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */
#pragma once

#include <iostream>
#include <SDL.h>


class RENDERABLE {

public :

    virtual bool RenderObject( SDL_Renderer * render, int xOffset, int yOffset ) = 0;


};
