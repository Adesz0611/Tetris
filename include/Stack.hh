#ifndef STACK_H
#define STACK_H

#include <SDL2/SDL.h>
#include <cstdint>

#define ARRAY_SIZE(x) sizeof(x) / sizeof(x[0])

namespace Stack {

#ifdef WITH_COLORS
    constexpr SDL_Color Colors[] = {
        {.r = 0x03, .g = 0x41, .b = 0xAE}, // Kék
        {.r = 0x72, .g = 0xCB, .b = 0x3B}, // Zöld
        {.r = 0xFF, .g = 0xD5, .b = 0x00}, // Citromsárga
        {.r = 0xFF, .g = 0x97, .b = 0x1C}, // Narancssárga
        {.r = 0xFF, .g = 0x32, .b = 0x13}, // Piros
    };
#endif

    class Stack {
        public:
            Stack();
            void Draw(SDL_Renderer *p_renderer);
            bool area[20][10] {0};
#ifdef WITH_COLORS
            std::uint8_t color[20][10];
#endif
            ~Stack();
        private:
    };

}

#endif
