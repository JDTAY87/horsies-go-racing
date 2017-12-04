#include "hrhorsie.h"

int hrHorsie::horsievalues[] =
{
    2, 3, 5, 7, 11,
    13, 17, 19, 23, 29,
    31, 37, 41, 43, 47,
    53, 59, 61, 67, 999
};

const char* hrHorsie::printvalues[] =
{
    "  2", "  3", "  5", "  7", " 11",
    " 13", " 17", " 19", " 23", " 29",
    " 31", " 37", " 41", " 43", " 47",
    " 53", " 59", " 61", " 67", "999"
};

const char* hrHorsie::horsienames[] =
{
    "Chicken Dinner", "Speed Demon", "Granny Apple", "The Last Straw", "Five and Dime",
    "Sweet Dreams", "Nature Calling", "When in Doubt", "Highway Robbery", "Double Wide",
    "Dark and Stormy", "Look at Me", "Cop Out", "Wagon Wheel", "The Spanish Inquisition",
    "Diet Soda", "Mountain Man", "Take a Left", "Quiet Time", "Lastie"
};

hrHorsie::hrHorsie()
{
    horsieID = 0;
    shown = false;
    return;
}

void hrHorsie::show()
{
    shown = true;
    return;
}

void hrHorsie::hide()
{
    shown = false;
    return;
}

void hrHorsie::settexture( SDL_Texture* texturetoset )
{
    texture = texturetoset;
    return;
}

void hrHorsie::setsize( int w, int h )
{
    srcrect.w = w;
    dstrect.w = w;
    srcrect.h = h;
    dstrect.h = h;
    return;
}

void hrHorsie::setposition( int x, int y )
{
    dstrect.x = x;
    dstrect.y = y;
    return;
}

void hrHorsie::setframe( int frametoset )
{
    frame = frametoset;
    return;
}

void hrHorsie::sethorsieID( int ID )
{
    horsieID = ID;
    return;
}

const char* hrHorsie::gethorsiename()
{
    return horsienames[horsieID];
}

int hrHorsie::gethorsievalue()
{
    return horsievalues[horsieID];
}

const char* hrHorsie::getprintvalue()
{
    return printvalues[horsieID];
}

void hrHorsie::render( SDL_Renderer* renderer )
{
    if ( shown == true )
    {
        srcrect.x = frame % 16 * srcrect.w;
        srcrect.y = frame / 16 * srcrect.h;
        SDL_RenderCopy( renderer, texture, &srcrect, &dstrect );
    }
    return;
}

hrHorsie::~hrHorsie()
{
    return;
}
