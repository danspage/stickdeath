#include "TestState.h"

#include "../graphics/Graphics.h"
#include "../graphics/Images.h"

void TestState::Update(float dt)
{
}

void TestState::Render()
{
    GameEngine::FillBG(SKYBLUE);

    GameEngine::FillRect(squareX, squareY, 10, 10, RED);

    GameEngine::DrawImage("images/sprites/entity/player_right", 0, 0, {.flipHorizontal=flipImg});
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
        flipImg = true;
        break;
    case KEY_RIGHT:
        squareX++;
        flipImg = false;
        break;
    default:
        break;
    }
}