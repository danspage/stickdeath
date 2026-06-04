#pragma once

#include <iostream>

#include "Tile.h"
#include "../../../../framework/util/Timer.h"

namespace StickDeath
{
    class SpikeTile : public Tile
    {
    private:
        bool touchingPlayer = false;
        bool touchedThisFrame = false;
        GameEngine::Util::Timer playerTouchTimer = GameEngine::Util::Timer(0.5f, true);
        Entity *targetedEntityForCollision;
        void HurtPlayer();

    public:
        SpikeTile(int x, int y);

        void Update(float dt) override;
        void OnCollision(Entity *entity, bool isInside) override;
    };
}