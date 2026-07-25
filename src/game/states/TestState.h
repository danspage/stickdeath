#pragma once

#include <deque>
#include <memory>

#include "../../engine/state/GameState.h"
#include "../../engine/graphics/Graphics.h"
#include "../../engine/graphics/Fonts.h"
#include "../../engine/graphics/Images.h"
#include "../world/entity/Player.h"
#include "../world/map/tile/Tile.h"
#include "../world/map/tile/SpikeTile.h"
#include "../world/map/Map.h"
#include "../ui/components/player/HealthBar.h"
#include "../world/particles/Particles.h"
#include "../../engine/basic_types/Positional.h"
#include "../../engine/util/Timer.h"

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

        std::deque<std::unique_ptr<Particles>> particles;

        GameEngine::Util::Timer floorParticlesTimer = GameEngine::Util::Timer(0.25, true);
    };
}