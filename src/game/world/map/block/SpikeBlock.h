#pragma once

#include <iostream>

#include "Block.h"
#include "../../../../framework/util/Timer.h"

namespace StickDeath
{
    class SpikeBlock : public Block
    {
    private:
        bool touchingPlayer = false;
        bool touchedThisFrame = false;
        GameEngine::Util::Timer playerTouchTimer = GameEngine::Util::Timer(0.5f, true);
        Entity* targetedEntityForCollision;
        void HurtPlayer();

    public:
        SpikeBlock(int x, int y);

        void Update(float dt) override;
        void OnCollision(Entity* entity, bool isInside) override;
    };
}