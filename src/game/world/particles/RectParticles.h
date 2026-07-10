#pragma once

#pragma once

#include "Particles.h"

#include "../../../framework/util/MathUtil.h"

namespace StickDeath
{
    class RectParticles : public Particles
    {
    public:
        RectParticles(
            const std::string &texture,
            const GameEngine::PointF &minPos,
            const GameEngine::PointF &maxPos,
            const GameEngine::PointF &velocity,
            const GameEngine::PointF &randomizeVelocity,
            const float destroyTime,
            const int count,
            const bool doCollision,
            const bool doGravity);
    };
}