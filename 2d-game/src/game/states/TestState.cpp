#include "TestState.h"

namespace StickDeath
{
    TestState::TestState() : GameState()
    {
        player.SetPos(3, 1);

        for (int x = 0; x < 10; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                StickDeath::Map::SetBlock(x * 5, y, "floor");
            }
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
    }

    void TestState::OnKeyPressed(int key)
    {
        if (key == KEY_ESCAPE)
        {
            GameEngine::SetState("title");
        }
    }
}