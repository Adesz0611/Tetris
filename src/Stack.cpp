#include <cstdio>
#include <SDL2/SDL.h>

#include "Stack.hh"
#include "Debug.hh"

namespace Stack {
    Stack::Stack() {
    }

    void Stack::Draw(SDL_Renderer *p_renderer) {
        SDL_Rect rec;
#ifndef WITH_COLORS
        rec.w = rec.h = 30;
#endif
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 10; j++) {
                if(area[i][j]) {
                    rec.y = i * 30;
#ifdef WITH_COLORS
                    rec.w = rec.h = 30 - 2 * OUTLINE;
                    rec.x = 100 + OUTLINE + j * 30;

                    if(j < 9) {
                        rec.w += OUTLINE;
                    }

                    rec.h += OUTLINE;

                    SDL_SetRenderDrawColor(p_renderer, Colors[color[i][j]].r, Colors[color[i][j]].g, Colors[color[i][j]].b, 255);
#else
                    rec.x = 100 + j * 30;
                    SDL_SetRenderDrawColor(p_renderer, 20, 20, 20, 255);
#endif
                    SDL_RenderFillRect(p_renderer, &rec);

#ifdef WITH_COLORS
                    // Kirajzoljuk a szegélyeket
                    SDL_SetRenderDrawColor(p_renderer, 20, 20, 20, 255);

                    // Felső
                    rec.x = 100 + j * 30;
                    rec.y = i * 30 - OUTLINE;
                    rec.w = 30 + OUTLINE;
                    rec.h = OUTLINE;
                    if(!area[i-1][j])
                        SDL_RenderFillRect(p_renderer, &rec);

                    // Alsó
                    rec.y = i * 30 + 30 - OUTLINE;
                    SDL_RenderFillRect(p_renderer, &rec);

                    // Bal oldali
                    rec.y = i * 30;
                    rec.w = OUTLINE;
                    rec.h = 30;
                    SDL_RenderFillRect(p_renderer, &rec);

                    // Jobb oldali
                    if(j > 8 || !area[i][j + 1]) {
                        rec.x = 100 + j * 30 + 30;
                        if(j > 8)
                            rec.x -= OUTLINE;
                        SDL_RenderFillRect(p_renderer, &rec);
                    }
#endif
                }
            }
        }

    }

    Stack::~Stack() {
    }
}
