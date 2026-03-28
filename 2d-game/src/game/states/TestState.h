#pragma once

#include "../../framework/state/GameState.h"
#include "../../framework/graphics/Graphics.h"
#include "../../framework/graphics/Fonts.h"
#include "../../framework/graphics/Images.h"
#include "../world/entity/Player.h"
#include "../world/map/block/Block.h"
#include "../world/map/Map.h"

namespace StickDeath
{
    class TestState : public GameEngine::GameState
    {
    public:
        TestState();

        // void OnEnter() override;
        // void onExit() override;
        void Update(float dt) override;
        void Render() override;
        void OnKeyPressed(int key) override;

    private:
        int squareX = 10;
        int squareY = 10;

        bool flipImg = false;

        Player player;
    };
}