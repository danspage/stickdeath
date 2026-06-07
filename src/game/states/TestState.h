#pragma once

#include "../../framework/state/GameState.h"
#include "../../framework/graphics/Graphics.h"
#include "../../framework/graphics/Fonts.h"
#include "../../framework/graphics/Images.h"
#include "../world/entity/Player.h"
#include "../world/map/tile/Tile.h"
#include "../world/map/tile/SpikeTile.h"
#include "../world/map/Map.h"
#include "../ui/components/player/HealthBar.h"

namespace StickDeath
{
    class TestState : public GameEngine::GameState
    {
    public:
        TestState();

        // void OnEnter() override;
        // void onExit() override;
        void Restart();
        void UpdateCameraPosition(float dt);
        void Update(float dt) override;
        void Render() override;
        void OnKeyPressed(SDL_Scancode key) override;
        void OnKeyHeld(SDL_Scancode key) override;
        void OnKeyReleased(SDL_Scancode key) override;

    private:
        float cameraTargetX = 0.0f;
        float cameraTargetY = 0.0f;
        const float cameraSmoothSpeed = 5.0f; // tune this for feel

        Player player = Player(0, 0);

        UI::HealthBar healthBar = UI::HealthBar(GameEngine::Colors::RED, 10, 20, GameEngine::WIDTH_VOXELS - 23, 1, 22, 5);
    };
}