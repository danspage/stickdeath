#pragma once

#include "../../framework/state/GameState.h"
#include "../../framework/graphics/Graphics.h"
#include "../../framework/graphics/Images.h"

class TestState : public GameEngine::GameState
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

    bool flipImg = false;
};