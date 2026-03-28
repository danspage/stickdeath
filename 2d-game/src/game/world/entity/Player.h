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
        Player() : Entity({12, 32}) {};

        void HandleKeyPress(int key);
        
        void Update(float dt) override;
        void Render() override;

    private:
        bool facingLeft = false;

        const float speed = 5;

        GameEngine::TextureAnimation playerAnim = GameEngine::TextureAnimation(0.1, {
                                                                                        "sprites/entity/player/walking_1",
                                                                                        "sprites/entity/player/walking_2",
                                                                                        "sprites/entity/player/walking_3",
                                                                                        "sprites/entity/player/walking_4",
                                                                                    });
    };
}