#include "TestState.h"

#include <format>
#include <algorithm>

#include "../../framework/GameEngine.h"
#include "../world/map/Map.h"
#include "../../framework/graphics/camera/Camera.h"

namespace StickDeath
{
    TestState::TestState() : GameState()
    {
        for (int x = 0; x < 50; x++)
        {
            StickDeath::Map::SetTile(x, 0, "floor");
        }

        for (int x = 0; x < 10; x++)
        {
            StickDeath::Map::SetTile(x * 5, x + 4, "floor");
        }

        StickDeath::Map::SetTile(1, 1, std::make_unique<SpikeTile>(1, 1));
    }

    void TestState::Restart()
    {
        player.SetPos(3, 1);
        player.SetHealth(player.GetMaxHealth());
        healthBar.SetValue(player.GetMaxHealth());
        GameEngine::SetState("title");
    }

    void TestState::UpdateCameraPosition(float dt)
    {
        // Calculate target camera position (player near center)
        const float playerWorldX = player.GetCollider()->GetXPos() * StickDeath::Map::TILE_SIZE;
        const float playerWorldY = player.GetCollider()->GetYPos() * StickDeath::Map::TILE_SIZE;

        cameraTargetX = playerWorldX - GameEngine::WIDTH_VOXELS * 0.5f;
        cameraTargetY = playerWorldY - GameEngine::HEIGHT_VOXELS * 0.35f;

        // Clamp target to world bounds
        const float maxCamX = StickDeath::Map::MAP_WIDTH * StickDeath::Map::TILE_SIZE - GameEngine::WIDTH_VOXELS;
        const float maxCamY = StickDeath::Map::MAP_HEIGHT * StickDeath::Map::TILE_SIZE - GameEngine::HEIGHT_VOXELS;

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
    }

    void TestState::Render()
    {
        GameEngine::FillBG(GameEngine::Colors::CRIMSON);

        StickDeath::Map::RenderMap();

        player.Render();

        GameEngine::DrawString(std::format("FPS: {}", GameEngine::GetFPS()), 2, 2, "default", GameEngine::Colors::YELLOW);

        GameEngine::DrawString(std::format("IsOnGround: {}", (player.GetCollider()->IsOnGround() ? "true" : "false")), 2, 32, "default", GameEngine::Colors::YELLOW);
        GameEngine::DrawString(std::format("X: {}", player.GetCollider()->GetXPos()), 2, 40, "default", GameEngine::Colors::YELLOW);
        GameEngine::DrawString(std::format("Y: {}", player.GetCollider()->GetYPos()), 2, 48, "default", GameEngine::Colors::YELLOW);

        healthBar.Render();
    }

    void TestState::OnKeyPressed(SDL_Scancode key)
    {
        if (key == SDL_SCANCODE_ESCAPE)
        {
            GameEngine::SetState("title");
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