/**
 *
 * MATEI GEORGE DANIEL
 * GRUPA 144
 * PROIECT GOMOKU
 */

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

#include "GAME_ZONE.h"
#include "MENU.h"
#include "GAME.h"

GAME* GAME :: _instance = NULL;


/*

	num = numarul de piese puse de pe masa

	mod = {-1	:neselectat
	      { 1	:swap
	      { 2	:swap2
	      { 3	:swap2->place2

	oriden in run() : action(x,y) -> logic() -> randare()

*/

void New() {

	// reset gamezone;
	// reset game { metoda stergere meniu temporar
	//	      { metoda reinitializare _player_to_move;

    GAME_ZONE *game_zone = game_zone->GetInstance();
    GAME *game = game ->GetInstance();

    game_zone->Reset();
    game->Reset();

}

void Quita () {


	std :: cout << "quit\n";
	GAME *game = game ->GetInstance();
    game -> Quit();

}

void Swap() {

	GAME* game = game -> GetInstance();
	GAME_ZONE *game_zone = game_zone->GetInstance();

	game ->ChangePlayerToMove();
	game_zone ->SetGameMod( 1 );


}

void Remiza( ) {



    static int player;
    static int tura;
    GAME_ZONE * game = game -> GetInstance( );
    GAME *game_zone = game_zone ->GetInstance();

    if ( !game-> Win() && ( ( game->GetNumberOfMoves() > 3 && game->GetMod() == 1 ) || ( game->GetMod() != 1 && game->GetNumberOfMoves() > 5 ) )  ){

        if ( game_zone->GetRemiza() == 0 ) {
            game_zone->ProposeRemiza();
            tura = game->GetNumberOfMoves();
        } else if ( game_zone->GetRemiza() == 1 ) {
            if ( tura == game ->GetNumberOfMoves() ) {
                game_zone->AceptRemiza();
            }
        }

    }

}

void ChoseBlack() {
    Swap();
    Swap();
}

void Place2() {

	GAME_ZONE *game_zone = game_zone -> GetInstance();
	GAME* game = game -> GetInstance();
	game_zone->SetGameMod( 3 );

}

void Decline ( ) {

    GAME *game = game->GetInstance();
    if ( game->GetRemiza() != 2 ) {
        game->DeclineRemiza();
    }

}

void GAME :: Logic() {
	GAME_ZONE *game_zone = game_zone->GetInstance();
	int num = game_zone -> GetNumberOfMoves();
	int mod = game_zone -> GetMod();

	if ( num == 3 ) {
		if (mod != 3 && temporar.GetSize() == 0 ) {
            ChangePlayerToMove();
            temporar.AddButton( (SDL_Rect){660,700,100,35}, Swap, "Chose Black" );
		} else if ( mod == 1 && temporar.GetSize() >= 1 ) {
            temporar.Clear();
		}
		if( mod == 2 )
			temporar.AddButton( (SDL_Rect){660,600,100,35}, Place2, "Place2" );
	}

	if ( num ==5 && mod == 3 ) {
        ChangePlayerToMove();
		temporar.AddButton( (SDL_Rect){660,700,100,35}, ChoseBlack, "ChoseBlack" );
	}


    if( (num != 3 && num != 5) || ( num == 3 && mod == 3 ) || ( num == 5 && mod == 1 ) ) {
		temporar.Clear();
	}


	if ( (num >= 4 && mod == 2) || ( num > 5 && mod == 3 ) || ( mod == 1 && num > 3 ) ) {
		ChangePlayerToMove();
	}

}

void SetSwap() {
    std :: cout << "Swap\n";
    GAME_ZONE * game = game -> GetInstance( );
    if ( game -> GetMod() == -1 )
        game -> SetGameMod( 1 );
}

void SetSwap2() {
    std :: cout << "Swap2\n";
    GAME_ZONE * game = game -> GetInstance( );
    if ( game -> GetMod() == -1 )
        game -> SetGameMod( 2 );
}

void Pas( ) { std :: cout << "Pas\n";

    GAME_ZONE * game = game -> GetInstance( );
    GAME *game_zone = game_zone ->GetInstance();
    if ( !game-> Win() && ( ( game->GetNumberOfMoves() > 3 && game->GetMod() == 1 ) || ( game->GetMod() != 1 && game->GetNumberOfMoves() > 5 ) )  ){
        game_zone ->ChangePlayerToMove();
        game->Pas();
    }

}

void f () { }

GAME :: GAME () {

    window = SDL_CreateWindow("bla",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, 0 );
    render = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );

    background = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET , 800, 800);


    GAME_ZONE * game = game -> GetInstance( (SDL_Rect){30, 30, 600, 690} );

    std :: vector < std :: pair < std :: pair < SDL_Rect, void (*)() >  ,  char * > > states;
    states.push_back( { {(SDL_Rect){ 660, 50, 100, 35 }, New }, "New"} );
    states.push_back( { {(SDL_Rect){ 660, 100, 100, 35 }, Quita }, "Quit"} );
    states.push_back( { {(SDL_Rect){ 660, 150, 100, 35 }, Remiza }, "Remiza"} );
    states.push_back( { { (SDL_Rect){660,250,100,35},Decline }, "Decline" } );
    states.push_back( { { (SDL_Rect){ 660, 200, 100, 35 } , Pas }, "Pas" } );

    MENU aux( (SDL_Rect){ 660, 0, 400, 800 }, states );
    meniu = aux;
    running = 1;
    _player_to_move = 1;
    _remiza = 0;

    states.clear();
    states.push_back( { { (SDL_Rect){ 350, 100, 100, 35 }, SetSwap }, "Swap" } );
    states.push_back( { { (SDL_Rect){ 350, 150, 100, 35 }, SetSwap2 }, "Swap2" } );
    MENU prim( (SDL_Rect){0,0,800,800}, states );
    SetOption = prim;

    MENU second( (SDL_Rect){660,600,140,200}, states );
    temporar = second;
    temporar.Clear();

}


bool GAME :: Action( int x, int y ) {
    GAME_ZONE * game = game -> GetInstance( (SDL_Rect){30, 30, 600, 690} );

    if ( game -> GetMod() == -1 ) {
        SetOption.ClickAction( x, y );
        return true;
    }
    int s = (GetRemiza() == 1 );
    if ( GetRemiza() == 0 ) {
        s += game -> ClickAction( x, y );
        s += temporar.ClickAction( x , y );
    };

    meniu.ClickAction( x, y );

    return s;
}

bool GAME :: Randare( ) {


    GAME_ZONE * game = game -> GetInstance( (SDL_Rect){30, 30, 600, 690} );
    SDL_SetRenderTarget( render, background );
    SDL_SetRenderDrawColor( render, 255, 255, 255, 255 );
    SDL_RenderClear( render );

    if ( game -> GetMod() == -1 ) {
        SetOption.RenderObject( render, 0, 0 );
    } else {

        game->RenderObject( render, 0, 0 );
        meniu.RenderObject( render, 0, 0 );
        temporar.RenderObject(render,0,0);
        RenderObject(render,0,0);
    }
    SDL_SetRenderTarget(render,NULL);
    SDL_RenderCopy( render, background, NULL, NULL );
    SDL_RenderPresent( render );

}

bool GAME :: RenderObject( SDL_Renderer *render, int xOffset, int yOffset) {

    TTF_Font* font = TTF_OpenFont( "../fonts/tnr.ttf", 100 );
    GAME_ZONE *game = game -> GetInstance();

    char A[2][50] = { "Player 1 to move", "Player 2 to move" };
    char B[2][50] = { "Winner player 1", "Winner player 2" };
    char C[2][50] = { " Black", " White" };
    char D[] = "| Se propune Remiza";
    char E[] = "Remiza";
    char Aux[100] = { "" };

    if ( !game->Win() ) {
        strcpy( Aux, A[_player_to_move-1] );
        strcat( Aux, C[game->GetNumberOfMoves()%2] );
    } else {
        strcpy( Aux, B[_player_to_move-1]);
        strcat( Aux, C[ (game->GetNumberOfMoves()-1)%2] );

    }

    if ( GetRemiza() == 1 ) {
        strcpy( Aux, D );
    } else if ( GetRemiza() == 2 ) {
        strcpy( Aux, E );
    }

    SDL_Surface* TextSurface = TTF_RenderText_Blended( font, Aux , {0,0,0});
    SDL_Texture *TextTexture = SDL_CreateTextureFromSurface( render, TextSurface );

    SDL_Rect posScris = (SDL_Rect){ 30, 730, 600, 40 };
    SDL_RenderCopy( render, TextTexture, NULL, &posScris );



}

void GAME :: Run() {

    GAME_ZONE *game = game -> GetInstance();
    Randare();

    while ( running ) {
    SDL_Event event;

        if ( SDL_PollEvent( &event ) ) {
            if ( event.type == SDL_MOUSEBUTTONDOWN ) {
                int x, y;
                SDL_GetMouseState( &x, &y );
                if( Action(x,y) && !game->Win() ){
                    Logic();
                }

                Randare();

            }
            if (  event.type == SDL_QUIT )
                running = 0;
        }

    }
}

