#include <raylib.h>

#include "framework/GameEngine.h"
#include "framework/graphics/Graphics.h"
#include "framework/state/TestState.h"

int main()
{
    InitWindow(GameEngine::WIDTH_VOXELS * GameEngine::VOXEL_SIZE, GameEngine::HEIGHT_VOXELS * GameEngine::VOXEL_SIZE, GameEngine::WINDOW_TITLE);

    GameEngine::Initialize(
        "test",
        {
            {"test", new TestState()},
        }
    );

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
