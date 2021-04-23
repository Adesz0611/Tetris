#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL2/SDL.h>
#include <vector>

namespace Tetromino {
    enum Direction {
        LEFT = 0,
        RIGHT,
        DOWN
    };

    class Tetromino {
        public:
            Tetromino();
            void Rotate();
            void Draw(SDL_Renderer *p_renderer);
            void Generate();
            bool checkWallCollision(Direction dir);
            void setX(int p_x);
            void setY(int p_y);
            int getX();
            int getY();
            void setMerged(bool p_m) { merged = p_m; }
            bool getMerged() { return merged; }
            ~Tetromino();
        private:
            std::vector<std::vector<bool>> tetromino;
            int x, y;
            bool merged;
    };
}

#endif
