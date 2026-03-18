#include "TitleState.h"

void TitleState::Render()
{
    GameEngine::FillBG(114, 47, 55);

    GameEngine::DrawString("Stickdeath", GameEngine::WIDTH_VOXELS / 2, 30, "title", Color({40, 40, 40}), {.alignment = GameEngine::GameFontAlignment::CENTER});

    GameEngine::FillRect(50, GameEngine::HEIGHT_VOXELS / 2 - 35, GameEngine::WIDTH_VOXELS - 100, 20, Color({40, 40, 40}));
    GameEngine::DrawString("Play", GameEngine::WIDTH_VOXELS / 2, GameEngine::HEIGHT_VOXELS / 2 - 28, "default", optionsIndex == 0 ? RED : YELLOW, {.alignment = GameEngine::GameFontAlignment::CENTER});

    GameEngine::FillRect(50, GameEngine::HEIGHT_VOXELS / 2 - 10, GameEngine::WIDTH_VOXELS - 100, 20, Color({40, 40, 40}));
    GameEngine::DrawString("Options", GameEngine::WIDTH_VOXELS / 2, GameEngine::HEIGHT_VOXELS / 2 - 3, "default", optionsIndex == 1 ? RED : YELLOW, {.alignment = GameEngine::GameFontAlignment::CENTER});

    GameEngine::FillRect(50, GameEngine::HEIGHT_VOXELS / 2 + 15, GameEngine::WIDTH_VOXELS - 100, 20, Color({40, 40, 40}));
    GameEngine::DrawString("Exit Game", GameEngine::WIDTH_VOXELS / 2, GameEngine::HEIGHT_VOXELS / 2 + 22, "default", optionsIndex == 2 ? RED : YELLOW, {.alignment = GameEngine::GameFontAlignment::CENTER});
}

void TitleState::Update(float dt)
{
}

void TitleState::OnKeyPressed(int key)
{
    switch (key)
    {
    case KEY_UP:
        optionsIndex -= 1;
        if (optionsIndex < 0)
            optionsIndex = 2;
        break;
    case KEY_DOWN:
        optionsIndex += 1;
        if (optionsIndex > 2)
            optionsIndex = 0;
        break;
    case KEY_ENTER:
        if (optionsIndex == 0)
        {
            GameEngine::SetState("test");
        }
        else if (optionsIndex == 2)
        {
            GameEngine::Shutdown();
        }
        break;
    default:
        break;
    }
}