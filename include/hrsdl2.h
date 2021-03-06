#ifndef HRSDL2_H
#define HRSDL2_H
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

class hrSDL2
{
    public:
        hrSDL2();
        bool start();
        SDL_Window* getwindow();
        SDL_Renderer* getrenderer();
        ~hrSDL2();

    protected:

    private:
        bool SDL2start();
        bool imagestart();
        bool mixerstart();
        bool windowstart();
        bool rendererstart();
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_GameController* controller;
};

#endif // HRSDL2_H
