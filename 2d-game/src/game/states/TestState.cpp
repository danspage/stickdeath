#include "TestState.h"

namespace StickDeath
{
    void TestState::OnLoad()
    {
        player.SetPos(50, 50);
    }

    void TestState::Update(float dt)
    {
        player.Update(dt);
    }

    void TestState::Render()
    {
        GameEngine::FillBG(SKYBLUE);

        player.Render();

        testBlock.Render();
    }

    void TestState::OnKeyPressed(int key)
    {
        if (key == KEY_ESCAPE)
        {
            GameEngine::SetState("title");
        }
    }
}