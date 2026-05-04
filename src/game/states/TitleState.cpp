#include "TitleState.h"

namespace StickDeath
{
    void TitleState::Render()
    {
        GameEngine::FillBG(114, 47, 55);

        GameEngine::DrawString("Stickdeath", GameEngine::WIDTH_VOXELS / 2, 30, "title", GameEngine::Color({40, 40, 40}), {.alignment = GameEngine::GameFontAlignment::CENTER});

        GameEngine::FillRect(50, GameEngine::HEIGHT_VOXELS / 2 - 35, GameEngine::WIDTH_VOXELS - 100, 20, GameEngine::Color({40, 40, 40}));
        GameEngine::DrawString("Play", GameEngine::WIDTH_VOXELS / 2, GameEngine::HEIGHT_VOXELS / 2 - 28, "default", optionsIndex == 0 ? GameEngine::Colors::RED : GameEngine::Colors::YELLOW, {.alignment = GameEngine::GameFontAlignment::CENTER});

        GameEngine::FillRect(50, GameEngine::HEIGHT_VOXELS / 2 - 10, GameEngine::WIDTH_VOXELS - 100, 20, GameEngine::Color({40, 40, 40}));
        GameEngine::DrawString("Options", GameEngine::WIDTH_VOXELS / 2, GameEngine::HEIGHT_VOXELS / 2 - 3, "default", optionsIndex == 1 ? GameEngine::Colors::RED : GameEngine::Colors::YELLOW, {.alignment = GameEngine::GameFontAlignment::CENTER});

        GameEngine::FillRect(50, GameEngine::HEIGHT_VOXELS / 2 + 15, GameEngine::WIDTH_VOXELS - 100, 20, GameEngine::Color({40, 40, 40}));
        GameEngine::DrawString("Exit Game", GameEngine::WIDTH_VOXELS / 2, GameEngine::HEIGHT_VOXELS / 2 + 22, "default", optionsIndex == 2 ? GameEngine::Colors::RED : GameEngine::Colors::YELLOW, {.alignment = GameEngine::GameFontAlignment::CENTER});
    }

    void TitleState::Update(float dt)
    {
    }

    void TitleState::OnKeyPressed(GameEngine::Key key)
    {
        switch (key)
        {
        case GameEngine::Key::UP:
            optionsIndex -= 1;
            if (optionsIndex < 0)
                optionsIndex = 2;
            break;
        case GameEngine::Key::DOWN:
            optionsIndex += 1;
            if (optionsIndex > 2)
                optionsIndex = 0;
            break;
        case GameEngine::Key::ENTER:
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
}