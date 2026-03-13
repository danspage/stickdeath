#include <raylib.h>

#include "framework/GameEngine.h"
#include "framework/graphics/Graphics.h"
#include "game/states/TestState.h"
#include "game/states/TitleState.h"
#include "framework/file_io/AssetLoader.h"

int main()
{
    InitWindow(GameEngine::WIDTH_VOXELS * GameEngine::VOXEL_SIZE, GameEngine::HEIGHT_VOXELS * GameEngine::VOXEL_SIZE, GameEngine::WINDOW_TITLE);

    GameEngine::InitializeRoutes(
        "title",
        {
            {"test", new TestState()},
            {"title", new TitleState()},
        }
    );

    GameEngine::LoadAllAssets();

    SetTargetFPS(GameEngine::TARGET_FPS);
    InitAudioDevice();

    while (!WindowShouldClose() && !GameEngine::_shuttingDown)
    {
        BeginDrawing();

        GameEngine::ProcessKeyEvents();

        GameEngine::UpdateCurrentState(GetFrameTime());

        GameEngine::RenderCurrentState();

        EndDrawing();
    }

    GameEngine::Cleanup();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
