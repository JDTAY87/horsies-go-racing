#include <random>
#include <chrono>
#include "hrsdl2.h"
#include "hrtexture.h"
#include "hrmessage.h"
#include "hrhorsie.h"
#define HORSIE_COUNT 5
#define MESSAGE_COUNT 13

class hrGame
{
public:
    bool initialize();
    void mainloop();
private:
    void settextures();
    void titlescreen();
    void choosehorse();
    void horserace();
    void showrace();
    void updatescreen();
    hrSDL2 SDL2;
    hrTexture fonttexture;
    hrTexture horsietexture;
    hrHorsie horsie[HORSIE_COUNT];
    hrMessage message[MESSAGE_COUNT];
    int functcounter;
    int cursorpos;
    int places[HORSIE_COUNT];
    int time;
};

bool hrGame::initialize()
{
    bool success = true;
    if ( !SDL2.start() ) { success = false; }
    else if ( !fonttexture.load( SDL2.getrenderer(), "jfont.png" ) ) { success = false; }
    else if ( !horsietexture.load( SDL2.getrenderer(), "horsie.png" ) ) { success = false; }
    else
    {
        hrGame::settextures();
        hrGame::titlescreen();
    }
    return success;
}

void hrGame::settextures()
{
    for ( int z = 0; z < MESSAGE_COUNT; z++ )
    {
        message[z].setfont( fonttexture.gettexture() );
        message[z].setfontsize( 10, 10 );
    }
    for ( int z = 0; z < HORSIE_COUNT; z++ )
    {
        horsie[z].settexture( horsietexture.gettexture() );
        horsie[z].setsize( 20, 20 );
    }
    return;
}

void hrGame::titlescreen()
{
    message[0].setposition( 80, 80 );
    message[0].setmessage( "Horsies Go Racing" );
    message[0].show();
    horsie[0].setposition( 140, 50 );
    horsie[0].setframe( 0 );
    horsie[0].show();
    horsie[1].setposition( 160, 50 );
    horsie[1].setframe( 1 );
    horsie[1].show();
    functcounter = 0;
    return;
}

void hrGame::choosehorse()
{
    for ( int z = 0; z < HORSIE_COUNT; z++ )
    {
        horsie[z].setframe( 0 );
        horsie[z].setposition( 50, 20 + z * 30 );
        horsie[z].show();
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator( seed );
    std::uniform_int_distribution<int> distribution( 0, 19 );
    int ID[HORSIE_COUNT];
    bool picked[20];
    for ( int z = 0; z < 20; z++ ) { picked[z] = false; }
    for ( int z = 0; z < HORSIE_COUNT; z++ )
    {
        bool goodpick = false;
        while ( goodpick == false )
        {
            ID[z] = distribution( generator );
            if ( picked[ID[z]] == false ) { picked[ID[z]] = true; goodpick = true; }
        }
    }
    for ( int z = 0; z < HORSIE_COUNT; z++ )
    {
        horsie[z].sethorsieID( ID[z] );
        message[z].setmessage( horsie[z].getprintvalue() );
        message[z+HORSIE_COUNT].setmessage( horsie[z].gethorsiename() );
        message[z].setposition( 10, 30 + z * 30 );
        message[z+HORSIE_COUNT].setposition( 20, 40 + z * 30);
        message[z].show();
        message[z+HORSIE_COUNT].show();
    }
    message[HORSIE_COUNT*2+2].hide();
    message[HORSIE_COUNT*2].setmessage( "Select horse:" );
    message[HORSIE_COUNT*2].setposition( 10, 10 );
    message[HORSIE_COUNT*2].show();
    message[HORSIE_COUNT*2+1].setmessage( ">" );
    message[HORSIE_COUNT*2+1].setposition( 10, 40 );
    message[HORSIE_COUNT*2+1].show();
    cursorpos = 0;
    functcounter = 1;
    return;
}

void hrGame::horserace()
{
    int pointrange = 0;
    for ( int z = 0; z < HORSIE_COUNT; z++ ) { pointrange += horsie[z].gethorsievalue(); }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator( seed );
    bool horsiepicked[HORSIE_COUNT];
    for ( int z = 0; z < HORSIE_COUNT; z++ ) { places[z] = 0; horsiepicked[z] = false; }
    for ( int z = 0; z < HORSIE_COUNT; z++ )
    {
        int selectedvaluetotal = 0;
        for ( int z2 = 0; z2 < HORSIE_COUNT; z2++ ) { selectedvaluetotal += horsie[z2].gethorsievalue() * horsiepicked[z2]; }
        std::uniform_int_distribution<int> distribution( 1+selectedvaluetotal, pointrange );
        int pickhorsie = distribution( generator );
        int horsienumber = 0;
        int determinehorsie = selectedvaluetotal;
        bool determined = false;
        while ( determined == false )
        {
            determinehorsie += horsie[horsienumber].gethorsievalue() * !horsiepicked[horsienumber];
            if ( pickhorsie <= determinehorsie )
            {
                places[z] = horsienumber;
                horsiepicked[horsienumber] = true;
                determined = true;
            }
            horsienumber++;
        }
    }
    functcounter = 2;
    time = SDL_GetTicks();
    return;
}

void hrGame::showrace()
{
    message[HORSIE_COUNT*2].setmessage( "And they're off!" );
    int timeelapsed = SDL_GetTicks() - time;
    for ( int z = 0; z < HORSIE_COUNT; z++ )
    {
        if ( z+1 > timeelapsed/2000 )
        {
            horsie[places[z]].setposition( (50+timeelapsed/40) , 20 + places[z] * 30 );
            horsie[places[z]].setframe( timeelapsed / 80 % 2 );
        }
    }
    switch (timeelapsed/2000)
    {
    case 1:
        message[HORSIE_COUNT*2].setmessage( "One falls behind..." );
        break;
    case 2:
        message[HORSIE_COUNT*2].setmessage( "A pack emerges..." );
        break;
    case 3:
        message[HORSIE_COUNT*2].setmessage( "It's neck and neck!" );
        break;
    case 4:
        message[HORSIE_COUNT*2].setmessage( "We have a leader!" );
        break;
    case 5:
        message[HORSIE_COUNT*2].setmessage( "Winner: " );
        message[HORSIE_COUNT*2+2].setmessage( horsie[places[HORSIE_COUNT-1]].gethorsiename() );
        message[HORSIE_COUNT*2+2].setposition( 90, 10 );
        message[HORSIE_COUNT*2+2].show();
        functcounter = 0;
        break;
    }
}

void hrGame::mainloop()
{
    SDL_Event e;
    bool quit = false;
    bool fullscreen = false;
    bool minimized = false;
    void (hrGame::*functs[])() = { &hrGame::choosehorse, &hrGame::horserace };
    while ( !quit )
    {
        while ( SDL_PollEvent(&e) )
        {
            if ( e.type == SDL_QUIT ) { quit = true; }
            if ( e.window.event == SDL_WINDOWEVENT_MINIMIZED ) { minimized = true; }
            if ( e.window.event == SDL_WINDOWEVENT_RESTORED ) { minimized = false; }
            if ( e.key.type == SDL_KEYUP && minimized == false )
            {
                switch ( e.key.keysym.sym )
                {
                    case SDLK_F11:
                        fullscreen = !fullscreen;
                        SDL_SetWindowFullscreen( SDL2.getwindow(), SDL_WINDOW_FULLSCREEN_DESKTOP * fullscreen );
                        break;
                    case SDLK_x:
                        if ( functcounter != 2 ) { (this->*functs[functcounter])(); }
                        break;
                    case SDLK_UP:
                        if ( functcounter == 1 )
                        {
                            cursorpos = (cursorpos+4)%5;
                            message[HORSIE_COUNT*2+1].setposition( 10, 40 + cursorpos * 30 );
                        }
                        break;
                    case SDLK_DOWN:
                        if ( functcounter == 1 )
                        {
                            cursorpos = (cursorpos+1)%5;
                            message[HORSIE_COUNT*2+1].setposition( 10, 40 + cursorpos * 30 );
                        }
                        break;
                }
            }
        }
        if ( functcounter == 2 ) { hrGame::showrace(); }
        if ( minimized == true ) { SDL_Delay( 1 ); }
        else { hrGame::updatescreen(); }
    }
    return;
}

void hrGame::updatescreen()
{
    SDL_Renderer* renderer = SDL2.getrenderer();
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
    SDL_RenderClear( renderer );
    for ( int z = 0; z < MESSAGE_COUNT; z++ ) { message[z].render( renderer ); }
    for ( int z = 0; z < HORSIE_COUNT; z++ ) { horsie[z].render( renderer ); }
    SDL_RenderPresent( renderer );
    return;
}

int main( int argc, char* argv[] )
{
    hrGame game;
    if ( !game.initialize() )
    {
        printf( "Initialization failed." );
    }
    else
    {
        game.mainloop();
    }
    return 0;
}
