#pragma once

#include <vector>

#include "../../engine/state/GameState.h"

#include "../../engine/graphics/Graphics.h"
#include "../../engine/GameEngine.h"
#include "../../engine/graphics/Fonts.h"

namespace StickDeath
{
    class TitleState : public GameEngine::GameState
    {
    public:
        TitleState() : GameState() {};

        // void OnLoad() override;
        // void onExit() override;
        void Update(float dt) override;
        void Render() override;
        void OnKeyPressed(SDL_Scancode key) override;

    private:
        std::vector<std::string> options = {"Play", "Settings", "Quit Game"};
        int optionsIndex = 0;
    };
}