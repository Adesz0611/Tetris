#ifndef ENGINE_H
#define ENGINE_H

#include <SDL2/SDL.h>
#include <string>

#include "Stack.hh"
#include "Tetromino.hh"

namespace Engine {

class Engine {
    public:
        Engine(const std::string& p_title, uint32_t p_width, uint32_t p_height);

        void Run();

        SDL_Texture *LoadTexture(const std::string& p_path);
        void DrawTexture(SDL_Texture *p_texture, int p_x, int p_y);

        ~Engine();
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        uint32_t width;
        uint32_t height;
        std::string title;
        bool shouldClose;
        SDL_Texture *hatter;

        Stack::Stack stack;
        Tetromino::Tetromino tetromino;

        void EventHandling();
        void Draw();
};

}

#endif /* ENGINE_H */
