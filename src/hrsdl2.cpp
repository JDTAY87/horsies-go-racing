#include "hrsdl2.h"

hrSDL2::hrSDL2()
{
    return;
}

bool hrSDL2::start()
{
    bool success = true;
    if ( !hrSDL2::SDL2start() ) { success = false; }
    else if ( !hrSDL2::imagestart() ) { success = false; }
    else if ( !hrSDL2::windowstart() ) { success = false; }
    else if ( !hrSDL2::rendererstart() ) { success = false; }
    return success;
}

bool hrSDL2::SDL2start()
{
    bool success = true;
    if ( SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER) != 0 )
    {
        printf( "SDL_Init error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        controller = SDL_GameControllerOpen(0);
    }
    return success;
}

bool hrSDL2::imagestart()
{
    bool success = true;
    if ( (IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) != IMG_INIT_PNG )
    {
        printf( "IMG_Init error: %s\n", SDL_GetError() );
        success = false;
    }
    return success;
}

bool hrSDL2::windowstart()
{
    bool success = true;
    window = SDL_CreateWindow( "Horsies Go Racing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 180, SDL_WINDOW_RESIZABLE );
    if ( window == NULL )
    {
        printf( "SDL_CreateWindow error: %s\n", SDL_GetError() );
        success = false;
    }
    return success;
}

bool hrSDL2::rendererstart()
{
    bool success = true;
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC );
    if ( renderer == NULL )
    {
        printf( "SDL_CreateRenderer error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        SDL_RenderSetLogicalSize( renderer, 320, 180 );
        SDL_RenderSetIntegerScale( renderer, SDL_TRUE );
    }
    return success;
}

SDL_Renderer* hrSDL2::getrenderer()
{
    return renderer;
}

SDL_Window* hrSDL2::getwindow()
{
    return window;
}

hrSDL2::~hrSDL2()
{
    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    IMG_Quit();
    SDL_Quit();
    return;
}
