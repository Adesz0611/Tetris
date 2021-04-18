#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL2/SDL.h>

namespace Tetromino {
    class Tetromino {
        public:
            Tetromino();
            void Rotate();
            void Draw(SDL_Renderer *p_renderer);
            void Generate();
            void setX(int p_x);
            void setY(int p_y);
            int getX();
            int getY();
            ~Tetromino();
        private:
            bool tetromino[4][4] {0};
            int x, y;
    };
}

#endif
