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
    std::vector<std::vector<std::vector<bool>>> tetro_array = {
//    static bool tetro_array[5][4][4] = {
        {
            {0,1,0},
            {1,1,1},
            {0,0,0},
        },
        {
            {1,0,0},
            {1,1,1},
            {0,0,0},
        },
        {
            {0,0,1},
            {1,1,1},
            {0,0,0},
        },
        {
            {1,1},
            {1,1},
        },
        {
            {0,1,1},
            {1,1,0},
            {0,0,0},
        },
        {
            {1,1,0},
            {0,1,1},
            {0,0,0},
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
        uint8_t generated = rand() % tetro_array.size();
        tetromino = {};
        for(int i = 0; i < tetro_array[generated][0].size(); i++) {
            std::vector<bool> tmp;
            for(int j = 0; j < tetro_array[generated][1].size(); j++) {
                tmp.push_back(tetro_array[generated][j][i]);
            }
            tetromino.push_back(tmp);
        }
    }

    void Tetromino::Rotate() {
        // Consider all squares one by one
        for (int x = 0; x < tetromino.size() / 2; x++) {
            // Consider elements in group
            // of 4 in current square
            for (int y = x; y < tetromino.size() - x - 1; y++) {
                // Store current cell in
                // temp variable
                bool temp = tetromino[x][y];
     
                // Move values from right to top
                tetromino[x][y] = tetromino[y][tetromino.size() - 1 - x];
     
                // Move values from bottom to right
                tetromino[y][tetromino.size() - 1 - x]
                    = tetromino[tetromino.size() - 1 - x][tetromino.size() - 1 - y];
     
                // Move values from left to bottom
                tetromino[tetromino.size() - 1 - x][tetromino.size() - 1 - y]
                    = tetromino[tetromino.size() - 1 - y][x];
     
                // Assign temp to left
                tetromino[tetromino.size() - 1 - y][x] = temp;
            }
        }
    }

    void Tetromino::Draw(SDL_Renderer *p_renderer) {
        SDL_Rect rect = {0,0,30,30};
        for(int i = 0; i < tetromino.size(); i++) {
            for(int j = 0; j < tetromino.size(); j++) {
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
