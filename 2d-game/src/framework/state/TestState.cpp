#include "TestState.h"

#include "../graphics/Graphics.h"

void TestState::Update(float dt)
{
}

void TestState::Render()
{
    GameEngine::Graphics::FillBG(SKYBLUE);

    GameEngine::Graphics::FillRect(squareX, squareY, 10, 10, RED);
}

void TestState::OnKeyPressed(int key)
{
    switch (key)
    {
    case KEY_UP:
        squareY--;
        break;
    case KEY_DOWN:
        squareY++;
        break;
    case KEY_LEFT:
        squareX--;
        break;
    case KEY_RIGHT:
        squareX++;
        break;
    default:
        break;
    }
}