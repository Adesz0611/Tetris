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
        Reset();
    }

    void Tetromino::Reset() {
        y = 0;
        x = 3;
        merged = false;
#ifdef WITH_COLORS
        color = rand() % ARRAY_SIZE(Stack::Colors);
#endif
        Generate();
    }

    void Tetromino::Reset(Stack::Stack p_stack) {
        y = 0;
        x = 3;
        merged = false;
#ifdef WITH_COLORS
        color = rand() % ARRAY_SIZE(Stack::Colors);
#endif
        Generate();
/*
        if(checkFullStackCollision(p_stack)) {
            Debug::Error("Vége a játéknak!");
            SDL_Delay(5000);
        }
*/
}

    void Tetromino::Generate() {
        uint8_t generated = rand() % tetro_array.size();
        tetromino = tetro_array[generated];
    }

    bool Tetromino::checkWallCollision(Direction dir) {
        if(dir == LEFT) {
            if(x < 0) {
                for(int i = 0; i < tetromino.size(); i++) {
                    if(tetromino[i][std::abs(x) - 1] == true)
                        return true;
                }
            }
        }
        else if (dir == RIGHT) {
            if((x + tetromino.size()) > 10) {
                for(int i = 0; i < tetromino.size(); i++) {
                    if(tetromino[i][tetromino.size() - (x + tetromino.size() - 10)] == true)
                        return true;
                }
            }
        }
        else if (dir == DOWN) {
            if(y + tetromino.size() > 19) {
                for(int j = 0; j < tetromino.size(); j++) {
                    if(tetromino[19-y][j] == true) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    bool Tetromino::checkStackCollision(Direction dir, Stack::Stack stack) {
#if 0
        if(dir == DOWN) {
            //Debug::Error("stack[0][2]: %d", stack.area[9][19]);
            for(int i = 0; i < tetromino.size(); i++) {
                //Debug::Error("X: %d, Y: %d\tX: %d, Y: %d", i, tetromino.size()-1, x+i, y+tetromino.size()-1);
                if(/*tetromino[i][tetromino.size() - 1] == true && */stack.area[x + i][y + tetromino.size() - 1] == true) {
                    //Debug::Error("Collide!");
                    return true;
                }
            }
        }
#endif
        return false;
    }

    bool Tetromino::checkFullStackCollision(Stack::Stack stack) {
        for(int i = 0; i < tetromino.size(); i++) {
            for(int j = 0; j < tetromino.size(); j++) {
                if(stack.area[y + i][x + j] == true && tetromino[i][j] == true) {
//                    merged = true;
                    Debug::Log("Collide!");
                    return true;
                }
            }
        }
        return false;
    }

    void Tetromino::Rotate() {
        for (int i = 0; i < tetromino.size() / 2; i++) {
            for (int j = i; j < tetromino.size() - i - 1; j++) {
                bool temp = tetromino[i][j];
     
                tetromino[i][j] = tetromino[tetromino.size() - 1 - j][i];
     
                tetromino[tetromino.size() - 1 - j][i] = tetromino[tetromino.size() - 1 - i][tetromino.size() - 1 - j];
     
                tetromino[tetromino.size() - 1 - i][tetromino.size() - 1 - j] = tetromino[j][tetromino.size() - 1 - i];
     
                tetromino[j][tetromino.size() - 1 - i] = temp;
            }
        }
    }

    void Tetromino::MergeToStack(Stack::Stack *p_stack) {
        for(int i = 0; i < tetromino.size(); i++) {
            for(int j = 0; j < tetromino.size(); j++) {
                if(tetromino[i][j]) {
                    p_stack->area[y + i][x + j] = 1;
#ifdef WITH_COLORS
                    p_stack->color[y + i][x + j] = color;
#endif
                }
            }
        }
        
        
        bool can;
        for(int i = 0; i < tetromino.size(); i++) {
            can = true;
            for(int j = 0; j < 10; j++) {
                if(p_stack->area[y + i][j] == false)
                    can = false;
            }
            if(can) {
                Debug::Log("Történik a csoda!");
                for(int k = y + i; k > 0; k--) {
                    for(int l = 0; l < 10; l++) {
                        p_stack->area[k][l] = p_stack->area[k-1][l];
#ifdef WITH_COLORS
                        p_stack->color[k][l] = p_stack->color[k-1][l];
#endif
                    }
                }
            }
        }
        Reset(*p_stack);

    }

    void Tetromino::Draw(SDL_Renderer *p_renderer, Stack::Stack *stack) {
        SDL_Rect rec;
#ifndef WITH_COLORS
        rec.w = rec.h = 30;
#endif
        for(int i = 0; i < tetromino.size(); i++) {
            for(int j = 0; j < tetromino.size(); j++) {
                if(tetromino[i][j]) {
                    rec.y = y * 30 + i * 30;
#ifdef WITH_COLORS
                    rec.x = 100 + x * 30 + j * 30 + OUTLINE;

                    rec.w = rec.h = 30 - 2 * OUTLINE;

                    if(x + j < 9) {
                        rec.w += OUTLINE;
                    }

                    rec.h += OUTLINE;

                    SDL_SetRenderDrawColor(p_renderer, Stack::Colors[color].r, Stack::Colors[color].g, Stack::Colors[color].b, 255);
#else
                    rec.x = 100 + x * 30 + j * 30;
                    SDL_SetRenderDrawColor(p_renderer, 20, 20, 20, 255);
#endif
                    SDL_RenderFillRect(p_renderer, &rec);

#ifdef WITH_COLORS
                    // Kirajzoljuk a szegélyeket
                    SDL_SetRenderDrawColor(p_renderer, 20, 20, 20, 255);

                    // Felső
                    rec.x = 100 + x * 30 + j * 30;
                    rec.y = i * 30  + y * 30 - OUTLINE;
                    rec.w = 30 + OUTLINE;
                    rec.h = OUTLINE;
                    if(!i || !tetromino[i-1][j])
                        SDL_RenderFillRect(p_renderer, &rec);

                    // Alsó
                    rec.y = i * 30 + y * 30 + 30 - OUTLINE;
                    SDL_RenderFillRect(p_renderer, &rec);

                    // Bal oldali
                    rec.y = i * 30 + y * 30;
                    rec.w = OUTLINE;
                    rec.h = 30;
                    SDL_RenderFillRect(p_renderer, &rec);

                    // Jobb oldali
                    if(j >= tetromino.size() - 1 || !tetromino[i][j + 1]) {
                        rec.x = 100 + j * 30 + x * 30 + 30;
                        if(x + j > 8)
                            rec.x -= OUTLINE;
                        SDL_RenderFillRect(p_renderer, &rec);
                    }
#endif

                }
            }
        }

        currentTime = SDL_GetTicks();
        if (currentTime > lastTime + 800) {
            if(checkWallCollision(Direction::DOWN))
                MergeToStack(stack);
            y++;
            if(checkFullStackCollision(*stack)) {
                y--;
                MergeToStack(stack);
            }
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
