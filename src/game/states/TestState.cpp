#include "TestState.h"

#include <format>
#include <algorithm>

#include "../../engine/GameEngine.h"
#include "../../engine/graphics/textures/TextureManager.h";

#include "../world/map/Map.h"
#include "../../engine/graphics/camera/Camera.h"
#include "../world/map/LevelLoader.h"
#include "../world/map/tile/Tiles.h"
#include "../world/particles/CircleParticles.h"
#include "../world/particles/ArcParticles.h"
#include "../world/particles/RectParticles.h"

namespace StickDeath
{
    TestState::TestState() : GameState()
    {
        LevelLoader::ApplyLevel(LevelLoader::ParseLevel("0"));

        player.SetPos(Map::spawnX, Map::spawnY);

        // for (int x = 0; x < 50; x++)
        // {
        //     StickDeath::Map::SetTile(x, 0, "floor");
        // }

        // for (int x = 0; x < 10; x++)
        // {
        //     StickDeath::Map::SetTile(x * 5, x + 4, "floor");
        // }

        // StickDeath::Map::SetTile(1, 1, std::make_unique<SpikeTile>(1, 1));
    }

    void TestState::OnEnter()
    {
        // Start all tile animation timers and reset their frames to 0
        for (auto &[tileName, animState] : _animationStates)
        {
            animState.animTimer.Restart();
            animState.currentFrame = 0;
        }

        floorParticlesTimer.Restart();
    }

    void TestState::onExit()
    {
        // Stop all tile animation timers
        for (auto &[tileName, animState] : _animationStates)
        {
            animState.animTimer.Stop();
        }

        for (std::unique_ptr<Particles> &p : particles)
        {
            p->Destroy();
        }
    }

    void TestState::Restart()
    {
        player.SetPos(Map::spawnX, Map::spawnY);
        player.SetHealth(player.GetMaxHealth());
        healthBar.SetValue(player.GetMaxHealth());
        GameEngine::SetState("title");
    }

    void TestState::UpdateCameraPosition(float dt)
    {
        // Calculate target camera position (player near center)
        const float playerWorldX = player.GetCollider()->GetXPos() * StickDeath::Map::TILE_SIZE_VOXELS;
        const float playerWorldY = player.GetCollider()->GetYPos() * StickDeath::Map::TILE_SIZE_VOXELS;
        const float worldHeightVoxels = static_cast<float>(StickDeath::Map::mapHeight * StickDeath::Map::TILE_SIZE_VOXELS);

        cameraTargetX = playerWorldX - GameEngine::WIDTH_VOXELS * 0.5f;
        cameraTargetY = StickDeath::Camera::y;

        // Use a vertical dead-zone so jumps do not cause abrupt camera snaps.
        const float topDeadZone = GameEngine::HEIGHT_VOXELS * 0.30f;
        const float bottomDeadZone = GameEngine::HEIGHT_VOXELS * 0.55f;
        const float playerScreenY = GameEngine::HEIGHT_VOXELS - (playerWorldY - StickDeath::Camera::y);

        if (playerScreenY < topDeadZone)
        {
            cameraTargetY += (topDeadZone - playerScreenY);
        }
        else if (playerScreenY > bottomDeadZone)
        {
            cameraTargetY -= (playerScreenY - bottomDeadZone);
        }

        // Clamp target to world bounds
        const float maxCamX = std::max(0.0f, static_cast<float>(StickDeath::Map::mapWidth * StickDeath::Map::TILE_SIZE_VOXELS - GameEngine::WIDTH_VOXELS));
        const float strictMaxCamY = std::max(0.0f, worldHeightVoxels - GameEngine::HEIGHT_VOXELS);
        const float maxCamY = std::max(strictMaxCamY, GameEngine::HEIGHT_VOXELS * 0.40f);

        cameraTargetX = std::clamp(cameraTargetX, 0.0f, maxCamX);
        cameraTargetY = std::clamp(cameraTargetY, 0.0f, maxCamY);

        // Smooth interpolation toward target
        const float easeAlpha = 1.0f - std::exp(-cameraSmoothSpeed * dt);
        const float currentCamX = StickDeath::Camera::x;
        const float currentCamY = StickDeath::Camera::y;

        const float newCamX = currentCamX + (cameraTargetX - currentCamX) * easeAlpha;
        const float newCamY = currentCamY + (cameraTargetY - currentCamY) * easeAlpha;

        StickDeath::Camera::SetPosition(newCamX, newCamY);
    }

    void TestState::Update(float dt)
    {
        

        Map::UpdateMap(dt);

        player.Update(dt);

        if (player.GetHealth() == 0 || player.GetY() < -200)
        {
            Restart();
        }

        healthBar.SetValue(player.GetHealth());

        UpdateCameraPosition(dt);

        UpdateTileAnimations(dt);

        for (std::unique_ptr<Particles> &p : particles)
        {
            p->Update(dt);
        }

        if (floorParticlesTimer.UpdateAndGetTicks(dt) > 0)
        {
            particles.emplace_back(new RectParticles(
                "blood_drop",
                GameEngine::PointF(6, 1),
                GameEngine::PointF(41, 1.3),
                GameEngine::PointF(0, 0.2),
                GameEngine::PointF(0, 0.1),
                2,
                20,
                true,
                false));
        }
    }

    void TestState::Render()
    {
        GameEngine::FillBG(GameEngine::Colors::WHITE);

        StickDeath::Map::RenderMap();

        player.Render();

        GameEngine::DrawString(std::format("FPS: {}", GameEngine::GetFPS()), 2, 2, "default", GameEngine::Colors::RED);

        GameEngine::DrawString(std::format("IsOnGround: {}", (player.GetCollider()->IsOnGround() ? "true" : "false")), 2, 10, "default", GameEngine::Colors::RED);
        GameEngine::DrawString(std::format("X: {}", player.GetCollider()->GetXPos()), 2, 18, "default", GameEngine::Colors::RED);
        GameEngine::DrawString(std::format("Y: {}", player.GetCollider()->GetYPos()), 2, 26, "default", GameEngine::Colors::RED);

        healthBar.Render();

        for (std::unique_ptr<Particles> &p : particles)
        {
            p->Render();
        }
    }

    void TestState::OnKeyPressed(SDL_Scancode key)
    {
        if (key == SDL_SCANCODE_ESCAPE)
        {
            GameEngine::SetState("title");
        }
        else if (key == SDL_SCANCODE_SPACE)
        {
            particles.emplace_back(new CircleParticles(
                "blood_drop",
                GameEngine::PointF(10, 13),
                GameEngine::PointF(0, 0),
                10,
                1.5,
                2.5,
                1000,
                true,
                true));
        }
        else if (key == SDL_SCANCODE_E)
        {
            if (player.IsFacingLeft())
            {
                // Left shoot particles
                particles.emplace_back(new ArcParticles(
                    "blood_drop",
                    GameEngine::PointF(player.GetX() - player.GetWidth() * 0.75, player.GetY() + Map::VoxelsToWorldUnits(26)),
                    {0, 0},
                    10,
                    3,
                    GameEngine::Util::AngleUnit::Degrees,
                    180,
                    135,
                    3,
                    100,
                    true,
                    false));
            }
            else
            {
                // Right shoot particles
                particles.emplace_back(new ArcParticles(
                    "blood_drop",
                    GameEngine::PointF(player.GetX() + player.GetWidth() * 0.75, player.GetY() + Map::VoxelsToWorldUnits(26)),
                    {0, 0},
                    10,
                    3,
                    GameEngine::Util::AngleUnit::Degrees,
                    0,
                    45,
                    3,
                    100,
                    true,
                    false));
            }
        }

        player.OnKeyPressed(key);
    }

    void TestState::OnKeyHeld(SDL_Scancode key)
    {
        player.OnKeyHeld(key);
    }

    void TestState::OnKeyReleased(SDL_Scancode key)
    {
        player.OnKeyReleased(key);
    }
}