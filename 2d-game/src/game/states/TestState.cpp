#include "TestState.h"

namespace StickDeath
{
    TestState::TestState() : GameState()
    {
        player.SetPos(3, 1);

        for (int x = 0; x < 50; x++)
        {
            StickDeath::Map::SetBlock(x, 0, "floor");
        }

        for (int x = 0; x < 10; x++)
        {
            StickDeath::Map::SetBlock(x * 5, x + 4, "floor");
        }
    }

    void TestState::Update(float dt)
    {
        player.Update(dt);
    }

    void TestState::Render()
    {
        GameEngine::FillBG(SKYBLUE);

        StickDeath::Map::Render();

        player.Render();

        GameEngine::DrawString(std::format("IsOnGround: {}", (player.IsOnGround() ? "true" : "false")), 2, 2, "default", YELLOW);
        GameEngine::DrawString(std::format("X: {}", player.GetXPos()), 2, 10, "default", YELLOW);
        GameEngine::DrawString(std::format("Y: {}", player.GetYPos()), 2, 18, "default", YELLOW);
    }

    void TestState::OnKeyPressed(int key)
    {
        if (key == KEY_ESCAPE)
        {
            GameEngine::SetState("title");
        }

        player.HandleKeyPress(key);
    }
}