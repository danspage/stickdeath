#include "Game.h"
#include "Graphics.h"
#include "Constants.h"
#include <iostream>

void Game::Render()
{
    scenes[currentScene]->DoKeyboardInput();
    scenes[currentScene]->Update();

    scenes[currentScene]->Render(graphics);

    // 1. If texture doesn't exist yet (ID is 0), create it
    if (texture.id == 0)
    {
        Image image = {
            .data = graphics.pixels,
            .width = widthVoxels * voxelSize,
            .height = heightVoxels * voxelSize,
            .mipmaps = 1,
            .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
        texture = LoadTextureFromImage(image);
    }
    // 2. If it exists, just update the pixel data (Much faster!)
    else
    {
        UpdateTexture(texture, graphics.pixels);
    }

    DrawTexture(texture, 0, 0, WHITE);
}