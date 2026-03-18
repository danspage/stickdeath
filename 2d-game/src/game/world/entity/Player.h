#pragma once

#include "Entity.h"

#include <vector>

#include "../../../framework/graphics/Graphics.h"
#include "../../../framework/graphics/Images.h"
#include "../../../framework/graphics/TextureAnimation.h"

class Player : public Entity
{
public:
    Player() : Entity({12, 32}) {};

    void Update(float dt) override;
    void Render() override;

private:
    bool facingLeft = false;

    const float speed = 50;

    GameEngine::TextureAnimation playerAnim = GameEngine::TextureAnimation(0.1, {
                                                                                    "images/sprites/entity/player/walking_1",
                                                                                    "images/sprites/entity/player/walking_2",
                                                                                    "images/sprites/entity/player/walking_3",
                                                                                    "images/sprites/entity/player/walking_4",
                                                                                });
};