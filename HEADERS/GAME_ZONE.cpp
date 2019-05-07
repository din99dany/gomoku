/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */

#include <SDL.h>
#include <iostream>
#include <cstring>
#include <cmath>
#include "GAME_ZONE.h"

void GAME_ZONE :: SetGameMod( int x ) {
    _Game_mod = x;
}

float GAME_ZONE :: TileSize() {

    return sqrt( _pos.w*_pos.h / ( 20 * 23 ) );

}

bool GAME_ZONE :: Win() {

    int i, j, s;
    int x_aa, y_aa;
    int A[ 23 ][ 23 ], B[23][23], C[23][23], D[23][23];


    for ( i = 0; i < 20; i++ ) {
        for ( j = 0; j < 23; ++j ) {
            A[ i ][ j ] = B[ i ][ j ] = C[ i ][ j ] = D[ i ][ j ] = 0;
        }
    }

    for (  i = 0; i < 20; ++i) {
        for ( j= 0; j < 23; ++j) {
            if ( _Tiles[ i ][ j ] == 1 ) {

                    if ( i >= 1 &&  _Tiles[ i ][ j ] == _Tiles[ i - 1 ][ j ] ) A[ i ][ j ] = A[ i - 1 ][ j ] + 1;
                    if ( j >= 1 && _Tiles[ i ][ j ] == _Tiles[ i ][ j - 1 ] ) B[ i ][ j ] = B[ i ][ j - 1 ] + 1;
                    if ( i >= 1 && j >= 1 && _Tiles[ i ][ j ] == _Tiles[ i - 1 ][ j - 1 ] ) C[ i ][ j] = C[ i - 1 ][ j - 1 ] + 1;
                    if ( i >= 1 && j <= 21 && _Tiles[ i ][j] == _Tiles[i-1][j+1]  ) D[ i ][ j ] = D[ i - 1 ][ j + 1 ] + 1;

            } else if ( _Tiles[ i ][ j ] == 2 ) {

                    if ( i >= 1 && _Tiles[ i ][ j ] == _Tiles[ i - 1 ][ j ] ) A[ i ][ j ] = A[ i - 1 ][ j ] - 1;
                    if ( j >= 1 && _Tiles[ i ][ j ] == _Tiles[ i ][ j - 1 ] ) B[ i ][ j ] = B[ i ][ j - 1 ] - 1;
                    if ( i >= 1 && j >= 1 && _Tiles[ i ][ j ] == _Tiles[ i - 1 ][ j - 1 ] ) C[ i ][ j] = C[ i - 1 ][ j - 1 ] - 1;
                    if ( i >= 1 && j <= 21 && _Tiles[ i ][j] == _Tiles[i-1][j+1]  ) D[ i ][ j ] = D[ i - 1 ][ j + 1 ] -1;

            }
        }
    }

    for ( i = 0; i < 20; ++i) {
        for ( j= 0 ; j < 23; ++j ){
            if ( A[ i ][ j ] >= 4 || B[ i ][ j ] >= 4 || C[ i ][ j ] >= 4 || D[ i ][ j ] >= 4 ) {
                std :: cout << "castigator player alb\n";
                return 1;
            }
            if ( A[ i ][ j ] <= -4 || B[ i ][ j ] <= -4 || C[ i ][ j ] <= -4 || D[ i ][ j ] <= -4 ) {
                std :: cout << "castigator player negru\n";
                return 1;
            }
        }
    }

    return 0;

}

void GAME_ZONE :: Reset() {

    _Game_mod = -1;
    _turn_counter = 0;

    for ( int i = 0; i < 20; ++i ) {
        for ( int j = 0; j < 23; ++j ) {
            _Tiles[ i ][ j ] = 0;
            _Pieces[ i ][ j ].Reset();
        }
    }

}

bool GAME_ZONE :: CheckPos( int x, int y ) {

    if ( _pos.x <= x && x <= _pos.x + _pos.w ) {
        if ( _pos.y <= y && y <= _pos.y + _pos.h )
            return true;
    }

    return false;

}

void GAME_ZONE :: SetPosition( SDL_Rect pos ) {
    _pos = pos;
}

void GAME_ZONE :: Swap() {

    int a, b;
    a = b = 0;
    char A[] = "../piesa2.bmp";
    char B[] = "../piesa1.bmp";

    for ( int i = 0; i < 20; ++i ) {
        for ( int j = 0; j < 23; ++j ) {
            if ( _Tiles[ i ][ j ] == 1 ) {
                _Pieces[ i ][ j ].SetPath( A );
                _Tiles[ i ][ j ] = 2;
            } else if ( _Tiles[ i ][ j ] == 2 ) {
                _Pieces[ i ][ j ].SetPath(B);
                _Tiles[ i ][ j ] = 1;
            }
        }
    }

}

bool GAME_ZONE :: ClickAction( int x, int y ) {

    x = (x + TileSize() / 2 ) / TileSize() * TileSize();
    y = (y + TileSize() / 2 ) / TileSize() * TileSize();

    if ( !CheckPos( x, y ) || Win() )
        return false;

    for ( int i = 0; i < 20; ++i  ) {
        for ( int j = 0;  j < 23; ++j ) {
            if ( !_Tiles[ i ][ j ] && _Pieces[ i ][ j ].ClickAction( x, y ) ) {
                _turn_counter++;
                _Pieces[ i ][ j ].SetTexturePath( (_turn_counter%2 == 1) ? ("../piesa1.bmp"):("../piesa2.bmp") );
                _Tiles[ i ][ j ] = ( _turn_counter%2==1 ) ? ( 1 ) : ( 2 );
                return true;
            }
        }
    }

    return false;

}

bool GAME_ZONE :: RenderObject( SDL_Renderer *render, int xOffset, int yOffset ) {

    SDL_SetRenderDrawColor( render, 0, 0, 0, 0 );
    for ( int i = 0; i < 19; ++i ) {
        for ( int j = 0; j < 22; ++j ) {
            SDL_Rect aux = (SDL_Rect){ i*TileSize() + _pos.x, j*TileSize()+_pos.y, TileSize(), TileSize() };
            SDL_RenderDrawRect( render, &aux );
        }
    }

    SDL_SetRenderDrawColor( render, 255, 255, 255, 0 );

    for ( int i = 0; i < 20; ++i ) {
        for ( int j = 0; j < 23; ++j ) {
            _Pieces[ i ][ j ].RenderObject( render, -TileSize()/2, -TileSize()/2 );
        }
    }

}


GAME_ZONE*  GAME_ZONE :: _instance = NULL;
int GAME_ZONE :: _turn_counter = 0;
