#include "TestState.h"

#include <format>

namespace StickDeath
{
    TestState::TestState() : GameState()
    {
        for (int x = 0; x < 50; x++)
        {
            StickDeath::Map::SetBlock(x, 0, "floor");
        }

        for (int x = 0; x < 10; x++)
        {
            StickDeath::Map::SetBlock(x * 5, x + 4, "floor");
        }

        StickDeath::Map::SetBlock(1, 1, std::make_unique<SpikeBlock>(1, 1));
    }

    void TestState::Update(float dt)
    {
        Map::UpdateMap(dt);

        player.Update(dt);

        healthBar.SetValue(player.GetHealth());
    }

    void TestState::Render()
    {
        GameEngine::FillBG(GameEngine::Colors::SKYBLUE);

        StickDeath::Map::RenderMap();

        player.Render();

        GameEngine::DrawString(std::format("FPS: {}", GetFPS()), 2, 2, "default", GameEngine::Colors::YELLOW);

        GameEngine::DrawString(std::format("IsOnGround: {}", (player.GetCollider()->IsOnGround() ? "true" : "false")), 2, 32, "default", GameEngine::Colors::YELLOW);
        GameEngine::DrawString(std::format("X: {}", player.GetCollider()->GetXPos()), 2, 40, "default", GameEngine::Colors::YELLOW);
        GameEngine::DrawString(std::format("Y: {}", player.GetCollider()->GetYPos()), 2, 48, "default", GameEngine::Colors::YELLOW);

        healthBar.Render();
    }

    void TestState::OnKeyPressed(GameEngine::Key key)
    {
        if (key == GameEngine::Key::ESCAPE)
        {
            GameEngine::SetState("title");
        }

        player.OnKeyPressed(key);
    }
}