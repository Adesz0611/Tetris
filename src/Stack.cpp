#include <cstdio>
#include <SDL2/SDL.h>

#include "Stack.hh"
#include "Debug.hh"

namespace Stack {
    Stack::Stack() {
    }

    void Stack::Draw(SDL_Renderer *p_renderer) {
        SDL_Rect rec;
        rec.w = 30;
        rec.h = 30;
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 10; j++) {
                if(area[i][j]) {
                    rec.x = 100 + j * 30;
                    rec.y = i * 30;
                    SDL_SetRenderDrawColor(p_renderer, 20, 20, 20, 255);
                    SDL_RenderFillRect(p_renderer, &rec);
                }
            }
        }

    }

    Stack::~Stack() {
    }
}
