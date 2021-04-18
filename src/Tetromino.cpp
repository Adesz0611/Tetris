#include <cstdlib>
#include "Tetromino.hh"

namespace Tetromino {
/*    static bool tetro_array[5][4][4] = {
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,1,0},
            {0,1,1,1}
        },
        {
            {0,0,0,0},
            {0,0,1,1},
            {0,0,1,0},
            {0,0,1,0}
        },
        {
            {0,0,0,0},
            {0,0,0,1},
            {0,0,1,1},
            {0,0,1,0}
        },
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,1,1},
            {0,0,1,1}
        },
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {1,1,1,1}
        }
    };*/
    static bool tetro_array[5][4][4] = {
        {
            {0,0,0,0},
            {0,0,1,0},
            {0,1,1,1},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {0,0,0,0},
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0}
        }
    };
    static unsigned int lastTime = 0, currentTime;
    Tetromino::Tetromino() {
        x = y = 0;
        Generate();
    }

    void Tetromino::Generate() {
        uint8_t generated = rand() % 5;
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                tetromino[i][j] = tetro_array[generated][j][i];
            }
        }
    }

    void Tetromino::Rotate() {
        bool tmp[4][4];
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                tmp[i][j] = tetromino[i][j];
            }
        }
        // Consider all squares one by one
        for (int x = 0; x < 2; x++) {
            // Consider elements in group
            // of 4 in current square
            for (int y = x; y < 4 - x - 1; y++) {
                // Store current cell in
                // temp variable
                bool temp = tetromino[x][y];
     
                // Move values from right to top
                tetromino[x][y] = tetromino[y][4 - 1 - x];
     
                // Move values from bottom to right
                tetromino[y][4 - 1 - x]
                    = tetromino[4 - 1 - x][4 - 1 - y];
     
                // Move values from left to bottom
                tetromino[4 - 1 - x][4 - 1 - y]
                    = tetromino[4 - 1 - y][x];
     
                // Assign temp to left
                tetromino[4 - 1 - y][x] = temp;
            }
        }
        /*
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                tetromino[i][j] = tmp[j][i];
            }
        }*/
    }

    void Tetromino::Draw(SDL_Renderer *p_renderer) {
        SDL_Rect rect = {0,0,30,30};
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                if(tetromino[i][j]) {
                    rect.x = 100 + x * 30 + i * 30;
                    rect.y = y * 30 + j * 30;
                    SDL_SetRenderDrawColor(p_renderer, 20, 20, 20, 255);
                    SDL_RenderFillRect(p_renderer, &rect);
                }
            }
        }

        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 800) {
            setY(getY() + 1);
            lastTime = currentTime;
        }
    }
    void Tetromino::setX(int p_x) { x=p_x; };
    void Tetromino::setY(int p_y) { y=p_y; };
    int  Tetromino::getX() { return x; };
    int  Tetromino::getY() { return y; };

    Tetromino::~Tetromino() {
    }
}
