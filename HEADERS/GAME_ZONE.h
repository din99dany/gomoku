/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */
#ifndef GAME_ZONE_H
#define GAME_ZONE_H

#include <iostream>
#include <SDL.h>
#include <vector>

#include "PIESA.h"
#include "CLICKABLE.h"
#include "RENDERABLE.h"

class GAME_ZONE : public CLICKABLE, public RENDERABLE {

    std :: vector < PIESA > _Pieces[ 20 ];
    int _Tiles[ 20 ][ 23 ];
    static int _turn_counter;
    SDL_Rect _pos;
    static GAME_ZONE * _instance;
    int _Game_mod;

    float TileSize();

    GAME_ZONE( SDL_Rect pos ) {
        _pos = pos;
        for ( int i = 0; i < 20; ++i ) {
            for ( int j = 0; j < 23; ++j ) {
                _Tiles[ i ][ j ] = 0;
                PIESA aux( (SDL_Rect){ i * TileSize()+_pos.y, j*TileSize()+_pos.y ,TileSize() ,TileSize()} );
                _Pieces[ i ].push_back( aux );
            }
        }
        _Game_mod = -1;
    }

public:

    static GAME_ZONE* GetInstance( SDL_Rect pos = (SDL_Rect){0,0,0,0}  ) {

        if ( _instance == NULL ) {
            _instance = new GAME_ZONE(pos);
        }

        return _instance;

    }
    void Swap();
    void Pas( int x = 1 ) { _turn_counter += x; }
    int GetNumberOfMoves() { return _turn_counter; }
    int GetMod() { return _Game_mod; }
    void SetGameMod( int x );
    void Reset();
    bool Win();
    bool CheckPos( int x, int y );
    void SetPosition( SDL_Rect pos );
    bool ClickAction( int x, int y );
    bool RenderObject( SDL_Renderer *render, int xOffset, int yOffset );

};

#endif // GAME_ZONE_H
