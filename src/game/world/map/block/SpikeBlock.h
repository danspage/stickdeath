#pragma once

#include "Block.h"

namespace StickDeath
{
    class SpikeBlock : public Block
    {
    private:
        bool touchingPlayer;

    public:
        SpikeBlock(int x, int y);

        void Update(float dt) override;
    };
}