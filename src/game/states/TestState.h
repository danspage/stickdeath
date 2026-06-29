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
#include "../world/particles/Particles.h"

namespace StickDeath
{
    class TestState : public GameEngine::GameState
    {
    public:
        TestState();

        void OnEnter() override;
        void onExit() override;
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

        UI::HealthBar healthBar = UI::HealthBar(GameEngine::Colors::BLACK, 10, 20, GameEngine::WIDTH_VOXELS - 23, 1, 22, 5);

        Particles testParticles = Particles(
            "blood_drop",
            GameEngine::PointF(5.0f, 15.0f),
            GameEngine::PointF(30.0f, 30.0f),
            GameEngine::PointF(3.0f, 3.0f),
            8.0f,
            5000,
            true,
            true);
    };
}