#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL2/SDL.h>
#include <vector>

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
            std::vector<std::vector<bool>> tetromino;
            int x, y;
    };
}

#endif
