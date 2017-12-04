#ifndef HRTEXTURE_H
#define HRTEXTURE_H
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class hrTexture
{
    public:
        hrTexture();
        bool load( SDL_Renderer* renderer, const char* filename );
        SDL_Texture* gettexture();
        ~hrTexture();

    protected:

    private:
        SDL_Texture* texture;
};

#endif // HRTEXTURE_H
