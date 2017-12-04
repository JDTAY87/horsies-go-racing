#ifndef HRHORSIE_H
#define HRHORSIE_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class hrHorsie
{
    public:
        hrHorsie();
        void show();
        void hide();
        void settexture( SDL_Texture* texturetoset );
        void setsize( int w, int h );
        void setposition( int x, int y );
        void setframe( int frametoset );
        void sethorsieID( int ID );
        const char* gethorsiename();
        int gethorsievalue();
        const char* getprintvalue();
        void render( SDL_Renderer* renderer );
        ~hrHorsie();

    protected:

    private:
        bool shown;
        SDL_Texture* texture;
        SDL_Rect srcrect;
        SDL_Rect dstrect;
        int frame;
        int horsieID;
        static int horsievalues[];
        static const char* printvalues[];
        static const char* horsienames[];
};

#endif // HRHORSIE_H
