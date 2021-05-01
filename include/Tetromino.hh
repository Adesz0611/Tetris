#ifndef TETROMINO_H
#define TETROMINO_H

#include <SDL2/SDL.h>
#include <vector>
#include "Stack.hh"

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
            void Draw(SDL_Renderer *p_renderer, Stack::Stack *stack);
            void Generate();
            bool checkWallCollision(Direction dir);
            bool checkStackCollision(Direction dir, Stack::Stack stack);
            bool checkFullStackCollision(Stack::Stack stack);
            void setX(int p_x);
            void setY(int p_y);
            int getX();
            int getY();
            void setMerged(bool p_m) { merged = p_m; }
            bool getMerged() { return merged; }
            ~Tetromino();
        private:
            void Reset();
            void MergeToStack(Stack::Stack *p_stack);
            std::vector<std::vector<bool>> tetromino;
            int x, y;
            bool merged;
    };
}

#endif
