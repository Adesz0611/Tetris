#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine.hh"


int main(int argc, char **argv)
{
    srand(time(NULL));

    Engine::Engine *engine = new Engine::Engine("Tetris by Adesz", 500, 600);
    engine->Run();
    delete engine;
    return 0;
}
