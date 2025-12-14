#include <raylib.h>
#include <vector>
#include "Game.h"
#include "Constants.h"
#include "Graphics.h"

int main()
{
    Game game = Game();
    game.graphics.Initialize();

    InitWindow(widthVoxels * voxelSize, heightVoxels * voxelSize, "2D Game");
    SetTargetFPS(targetFPS);
    InitAudioDevice();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // --- 3.3. Drawing (Draw) ---
        BeginDrawing();

        ClearBackground(BLACK); // Clear the frame buffer

        game.Render();

        // Optional: Draw other raylib elements (text, shapes)
        // DrawFPS(10, 10);

        EndDrawing(); // Swaps the buffers and displays the new frame
    }
}
