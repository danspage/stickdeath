#include <raylib.h>
#include <vector>
#include "Game.h"
#include "Constants.h"
#include "Graphics.h"

int main()
{
    Game game = Game();
    Graphics graphics;
    game.graphics = &graphics;
    SceneManager sceneManager;
    game.sm = &sceneManager;
    game.init();
    graphics.Initialize();

    InitWindow(widthVoxels * voxelSize, heightVoxels * voxelSize, "2D Game");
    SetTargetFPS(targetFPS);
    InitAudioDevice();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        BeginDrawing();

        game.Render();

        EndDrawing();
    }
}
