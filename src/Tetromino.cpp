#include <cstdlib>
#include <cmath>
#include "Tetromino.hh"
#include "Debug.hh"

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
        merged = false;
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

    bool Tetromino::checkWallCollision(Direction dir) {
        Debug::Log("X: %d", x);
        Debug::Log("Y: %d", y);
        if(dir == LEFT) {
            if(x < 0) {
                for(int j = 0; j < tetromino.size(); j++) {
                    if(tetromino[std::abs(x) - 1][j] == true)
                        return true;
                }
            }
        }
        else if (dir == RIGHT) {
            if((x + tetromino.size()) > 10) {
                for(int j = 0; j < tetromino.size(); j++) {
                    if(tetromino[tetromino.size() - (x + tetromino.size() - 10)][j] == true)
                        return true;
                }
            }
        }
        else if (dir == DOWN) {
            if(y + tetromino.size() > 19) {
                for(int i = 0; i < tetromino.size(); i++) {
                    if(tetromino[i][19-y] == true) {
                        merged = true;
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void Tetromino::Rotate() {
        for (int x = 0; x < tetromino.size() / 2; x++) {
            for (int y = x; y < tetromino.size() - x - 1; y++) {
                bool temp = tetromino[x][y];
     
                tetromino[x][y] = tetromino[y][tetromino.size() - 1 - x];
     
                tetromino[y][tetromino.size() - 1 - x]
                    = tetromino[tetromino.size() - 1 - x][tetromino.size() - 1 - y];
     
                tetromino[tetromino.size() - 1 - x][tetromino.size() - 1 - y]
                    = tetromino[tetromino.size() - 1 - y][x];
     
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
            checkWallCollision(Direction::DOWN);
            if(!merged)
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
