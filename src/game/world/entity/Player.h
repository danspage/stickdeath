#pragma once

#include "Entity.h"

#include <vector>
#include <cmath>

#include "../../../framework/graphics/Graphics.h"
#include "../../../framework/graphics/Images.h"
#include "../../../framework/graphics/TextureAnimation.h"
#include "../map/Map.h"

#include <SDL2/SDL.h>

namespace StickDeath
{
    class Player : public Entity
    {
    public:
        static constexpr float WIDTH_VOXELS = 12.0f;
        static constexpr float HEIGHT_VOXELS = 32.0f;

        Player(float x, float y)
            : Entity("player", x, y, WIDTH_VOXELS / Map::TILE_SIZE_VOXELS, HEIGHT_VOXELS / Map::TILE_SIZE_VOXELS, true)
        {
            GetCollider()->EnableGravity();
        };

        int GetHealth() const { return health; }
        int GetMaxHealth() const { return maxHealth; }
        void SetHealth(int _health) { health = _health; }
        void AddHealth(int amount) { health = std::min(maxHealth, health + amount); }
        void RemoveHealth(int amount) { health = std::max(0, health - amount); }

        bool IsFacingLeft() const { return facingLeft; }

        void OnKeyPressed(SDL_Scancode key);
        void OnKeyHeld(SDL_Scancode key);
        void OnKeyReleased(SDL_Scancode key);

        void Update(float dt) override;
        void Render() override;

    private:
        bool facingLeft = false;

        const float speed = 5;
        const int maxHealth = 20;
        int health = maxHealth;

        GameEngine::TextureAnimation playerAnim = GameEngine::TextureAnimation(0.1, {
                                                                                        "sprites/entity/player/walking_1",
                                                                                        "sprites/entity/player/walking_2",
                                                                                        "sprites/entity/player/walking_3",
                                                                                        "sprites/entity/player/walking_4",
                                                                                    });
    };
}