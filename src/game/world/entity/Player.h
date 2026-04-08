#pragma once

#include "Entity.h"

#include <vector>
#include <cmath>

#include <raylib.h>

#include "../../../framework/graphics/Graphics.h"
#include "../../../framework/graphics/Images.h"
#include "../../../framework/graphics/TextureAnimation.h"
#include "../map/Map.h"

namespace StickDeath
{
    class Player : public Entity
    {
    public:
        static constexpr float WIDTH_PX = 12.0f;
        static constexpr float HEIGHT_PX = 32.0f;

        Player(float x, float y)
            : Entity(x, y, WIDTH_PX / Map::TILE_SIZE, HEIGHT_PX / Map::TILE_SIZE, true)
        {
            GetCollider()->EnableGravity();
        };

        int GetHealth() const { return health; }
        void SetHealth(int _health) { health = _health; }
        void AddHealth(int amount) { health = std::min(maxHealth, health + amount); }
        void RemoveHealth(int amount) { health = std::max(0, health - amount); }

        void HandleKeyPress(int key);

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