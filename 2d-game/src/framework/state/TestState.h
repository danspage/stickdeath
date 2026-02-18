#pragma once

#include "GameState.h"

class TestState : public GameState
{
public:
    TestState() : GameState() {};

    // void OnLoad() override;
    // void onExit() override;
    void Update(float dt) override;
    void Render() override;
    void OnKeyPressed(int key) override;

    int squareX = 10;
    int squareY = 10;
};