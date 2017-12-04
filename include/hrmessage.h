#ifndef HRMESSAGE_H
#define HRMESSAGE_H
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class hrMessage
{
    public:
        hrMessage();
        void show();
        void hide();
        void setfontsize( int w, int h );
        void setposition( int x, int y );
        void setfont( SDL_Texture* texture );
        void setmessage( const char* text );
        void render( SDL_Renderer* renderer );
        ~hrMessage();

    protected:

    private:
        bool shown;
        SDL_Rect srcrect;
        SDL_Rect dstrect;
        SDL_Texture* font;
        const char* message;
};

#endif // HRMESSAGE_H
