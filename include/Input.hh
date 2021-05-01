#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "Tetromino.hh"

namespace Input {
    void keydown(SDL_Event *p_event, Tetromino::Tetromino *p_tetromino, Stack::Stack p_stack);
}

#endif
