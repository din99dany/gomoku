/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */
#pragma once

#include <iostream>
#include <SDL.h>

class CLICKABLE {

public :
    virtual bool ClickAction ( int x, int y ) = 0;

};

