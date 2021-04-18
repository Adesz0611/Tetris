#include <cstdio>
#include <cstdlib>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Engine.hh"

namespace Engine {

Engine::Engine (const std::string& p_title, uint32_t p_width, uint32_t p_height)
{
    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        std::fprintf(stderr, "Failed to initialize SDL2: %s\n", SDL_GetError());
        std::exit(EXIT_FAILURE);
    }

    if(!IMG_Init(IMG_INIT_PNG))
    {
        std::fprintf(stderr, "Failed to initialize SDL2 Image: %s", IMG_GetError());
        std::exit(EXIT_FAILURE);
    }

    window = SDL_CreateWindow(p_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, p_width, p_height, SDL_WINDOW_SHOWN);
    if(!window)
    {
        std::fprintf(stderr, "Failed to create SDL2 window: %s\n", SDL_GetError());
        std::exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        std::fprintf(stderr, "Failed to create SDL2 renderer: %s\n", SDL_GetError());
        std::exit(EXIT_FAILURE);
    }

    // Init
    shouldClose = false;
}

SDL_Texture *Engine::LoadTexture(const std::string& p_path)
{
    SDL_Texture *texture;

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", p_path.c_str());
    texture = IMG_LoadTexture(renderer, p_path.c_str());

    return texture;
}

void Engine::DrawTexture(SDL_Texture *p_texture, int p_x, int p_y)
{
    SDL_Rect dest;

    dest.x = p_x;
    dest.y = p_y;
    SDL_QueryTexture(p_texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, p_texture, NULL, &dest);
}

static void test() {
    std::printf("Teszt!\n");
}

void Engine::Run()
{
    hatter = LoadTexture("../gfx/hatter.png");

    while(!shouldClose)
    {
        // Event Handling
        EventHandling();

        // Input


        // Draw
        Draw();
        
        SDL_Delay(16);
        //SDL_Delay(750);
    }
}

void Engine::EventHandling()
{
    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_QUIT:
                shouldClose = true;
                break;
            case SDL_KEYDOWN:
                switch(e.key.keysym.scancode) {
                    case SDL_SCANCODE_RIGHT:
                        tetromino.setX(tetromino.getX() + 1);
                        printf("Nyom!");
                        break;
                    case SDL_SCANCODE_LEFT:
                        tetromino.setX(tetromino.getX() - 1);
                        printf("Nyom!");
                        break;
                    case SDL_SCANCODE_DOWN:
                        tetromino.setY(tetromino.getY() + 1);
                        printf("Nyom!");
                        break;
                    case SDL_SCANCODE_UP:
                        tetromino.Rotate();
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                break;
        }
    }
}

static void DrawWalls(SDL_Renderer *p_renderer) {
    SDL_Rect rect = {0,0,100,600};
    SDL_SetRenderDrawColor(p_renderer, 50, 157, 168, 255);
    SDL_RenderFillRect(p_renderer, &rect);
    rect.x = 400;
    SDL_RenderFillRect(p_renderer, &rect);
}

void Engine::Draw()
{
    // Clear
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw
    // DrawTexture(hatter, 0, 0);

    stack.Draw(renderer);
    tetromino.Draw(renderer);
    DrawWalls(renderer);

    // Present
    SDL_RenderPresent(renderer);
}

Engine::~Engine()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

}
