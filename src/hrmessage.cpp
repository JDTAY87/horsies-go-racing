#include "hrmessage.h"

hrMessage::hrMessage()
{
    shown = false;
    message = "";
    return;
}

void hrMessage::show()
{
    shown = true;
    return;
}

void hrMessage::hide()
{
    shown = false;
    return;
}

void hrMessage::setfontsize( int w, int h )
{
    srcrect.w = w;
    dstrect.w = w;
    srcrect.h = h;
    dstrect.h = h;
    return;
}

void hrMessage::setposition( int x, int y )
{
    dstrect.x = x;
    dstrect.y = y;
    return;
}

void hrMessage::setfont( SDL_Texture* texture )
{
    font = texture;
    return;
}

void hrMessage::setmessage( const char* text )
{
    message = text;
    return;
}

void hrMessage::render( SDL_Renderer* renderer )
{
    if ( shown == true )
    {
        int savex = dstrect.x;
        for ( int z = 0; message[z] != 0; z++ )
        {
            srcrect.x = message[z] % 16 * srcrect.w;
            srcrect.y = message[z] / 16 * srcrect.h;
            dstrect.x = savex + z * dstrect.w;
            SDL_RenderCopy( renderer, font, &srcrect, &dstrect );
        }
        dstrect.x = savex;
    }
    return;
}

hrMessage::~hrMessage()
{
    return;
}
