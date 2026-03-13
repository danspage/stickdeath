#pragma once

#include <vector>

#include "../../framework/state/GameState.h"

#include "../../framework/graphics/Graphics.h"
#include "../../framework/GameEngine.h"
#include "../../framework/graphics/Fonts.h"

class TitleState : public GameEngine::GameState
{
public:
    TitleState() : GameState() {};

    // void OnLoad() override;
    // void onExit() override;
    void Update(float dt) override;
    void Render() override;
    void OnKeyPressed(int key) override;

private:
    std::vector<std::string> options = {"Play", "Settings", "Quit Game"};
    int optionsIndex = 0;
};