#include <cstdio>
#include <SDL2/SDL.h>

#include "Stack.hh"

namespace Stack {
    Stack::Stack() {
        area[9][19] = 1;
        area[8][19] = 1;
        area[7][19] = 1;
        area[9][18] = 1;
    }

    void Stack::Draw(SDL_Renderer *p_renderer) {
        printf("\033[1m\033[36mEngine: \033[0mDraw\n");
        printf("\033[1m\033[36mEngine: \033[0m%p\n", p_renderer);
        SDL_Rect rec;
        rec.w = 30;
        rec.h = 30;
        for(int i = 0; i < 10; i++) {
            for(int j = 0; j < 20; j++) {
                if(area[i][j]) {
                    rec.x = 100 + i * 30;
                    rec.y = j * 30;
                    SDL_SetRenderDrawColor(p_renderer, 20, 20, 20, 255);
                    SDL_RenderFillRect(p_renderer, &rec);
                }
            }
        }

    }

    Stack::~Stack() {
    }
}
