#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <filesystem>

#include "engine/GameEngine.h"
#include "engine/graphics/Graphics.h"
#include "game/states/TestState.h"
#include "game/states/TitleState.h"
#include "engine/file_io/AssetLoader.h"

#include "game/Init.h"

int main(int argc, char **argv)
{
    if (argc > 0)
    {
        try
        {
            const std::filesystem::path executablePath = std::filesystem::absolute(argv[0]);
            const std::filesystem::path projectRoot = executablePath.parent_path().parent_path();

            // Keep relative asset paths stable no matter where the process is launched from.
            std::filesystem::current_path(projectRoot);
        }
        catch (const std::filesystem::filesystem_error &e)
        {
            throw std::runtime_error("Warning: could not set working directory: " + std::string(e.what()));
        }
    }

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
    {
        throw std::runtime_error("IMG_Init failed: " + std::string(IMG_GetError()));
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Stickdeath",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        GameEngine::WIDTH_PIXELS,
        GameEngine::HEIGHT_PIXELS,
        SDL_WINDOW_ALLOW_HIGHDPI);
    if (window == nullptr)
    {
        throw std::runtime_error("SDL_CreateWindow failed: " + std::string(SDL_GetError()));
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        throw std::runtime_error("SDL_CreateRenderer failed: " + std::string(SDL_GetError()));
        SDL_DestroyWindow(window);
        return 1;
    }

    GameEngine::LoadAllAssets();

    GameEngine::SetRenderer(renderer);

    StickDeath::InitGame();

    GameEngine::InitializeRoutes(
        "title",
        {
            {"test", new StickDeath::TestState()},
            {"title", new StickDeath::TitleState()},
        });

    bool running = true;
    SDL_Event event;

    const Uint64 perfFrequency = SDL_GetPerformanceFrequency();
    Uint64 prevCounter = SDL_GetPerformanceCounter();
    const double fixedDt = 1.0 / static_cast<double>(GameEngine::TARGET_UPDATE_HZ);
    const double maxFrameTime = 0.25;
    const int maxStepsPerFrame = 5;
    double accumulator = 0.0;

    while (running && !GameEngine::_shuttingDown)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        Uint64 currentCounter = SDL_GetPerformanceCounter();
        double frameTime = static_cast<double>(currentCounter - prevCounter) /
                           static_cast<double>(perfFrequency);
        prevCounter = currentCounter;

        if (frameTime > maxFrameTime)
        {
            frameTime = maxFrameTime;
        }

        accumulator += frameTime;

        int steps = 0;
        while (accumulator >= fixedDt && steps < maxStepsPerFrame)
        {
            GameEngine::ProcessKeyEvents();
            GameEngine::UpdateCurrentState(static_cast<float>(fixedDt));
            accumulator -= fixedDt;
            steps++;
        }

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
