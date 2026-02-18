#include "Game.h"
#include "Graphics.h"
#include "Constants.h"
#include <iostream>

#include "scenes/title/TitleScene.h"
#include "scenes/bouncing_ball/BouncingBallScene.h"

void Game::init()
{   
    sm->registerScene("title", std::make_unique<TitleScene>());
    sm->registerScene("bouncing_ball", std::make_unique<BouncingBallScene>());

    sm->markAsInitialized();

    sm->setScene("title");
}

void Game::Render()
{
    if (sm->getCurrentSceneName() == "NULL_SCENE")
    {
        std::cerr << "The game tried to loop but there was no scene set!" << std::endl;
        return;
    }

    sm->update();
    
    sm->render(graphics);

    // 1. If texture doesn't exist yet (ID is 0), create it
    if (texture.id == 0)
    {
        Image image = {
            .data = graphics->pixels,
            .width = widthVoxels * voxelSize,
            .height = heightVoxels * voxelSize,
            .mipmaps = 1,
            .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
        texture = LoadTextureFromImage(image);
    }
    // 2. If it exists, just update the pixel data (Much faster!)
    else
    {
        UpdateTexture(texture, graphics->pixels);
    }

    DrawTexture(texture, 0, 0, WHITE);
}