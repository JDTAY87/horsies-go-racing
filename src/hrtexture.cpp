#include "hrtexture.h"

hrTexture::hrTexture()
{
    return;
}

bool hrTexture::load( SDL_Renderer* renderer, const char* filename )
{
    bool success = true;
    SDL_Surface* surface = NULL;
    surface = IMG_Load( filename );
    if ( surface == NULL )
    {
        printf( "IMG_Load error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if ( texture == NULL )
        {
            printf( "SDL_CreateTextureFromSurface error: %s\n", SDL_GetError() );
            success = false;
        }
    }
    return success;
}

SDL_Texture* hrTexture::gettexture()
{
    return texture;
}

hrTexture::~hrTexture()
{
    SDL_DestroyTexture( texture );
    return;
}
