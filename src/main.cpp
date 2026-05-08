#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "framework/GameEngine.h"
#include "framework/graphics/Graphics.h"
#include "game/states/TestState.h"
#include "game/states/TitleState.h"
#include "framework/file_io/AssetLoader.h"

#include "game/Init.h"

int main()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
        std::cerr << "IMG_Init failed: " << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Stickdeath", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameEngine::WIDTH_PIXELS, GameEngine::HEIGHT_PIXELS, 0);
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        return 1;
    }

    GameEngine::SetRenderer(renderer);

    StickDeath::InitGame();

    GameEngine::InitializeRoutes(
        "title",
        {
            {"test", new StickDeath::TestState()},
            {"title", new StickDeath::TitleState()},
        });

    GameEngine::LoadAllAssets();

    bool running = true;
    SDL_Event event;

    Uint64 prevCounter = SDL_GetPerformanceCounter();

    while (running && !GameEngine::_shuttingDown)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        GameEngine::ProcessKeyEvents();

        Uint64 currentCounter = SDL_GetPerformanceCounter();
        double dt = static_cast<double>(currentCounter - prevCounter) /
                    static_cast<double>(SDL_GetPerformanceFrequency());
        prevCounter = currentCounter;

        GameEngine::UpdateCurrentState(static_cast<float>(dt));

        GameEngine::RenderCurrentState();
        SDL_RenderPresent(renderer);
    }

    GameEngine::Cleanup();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}
