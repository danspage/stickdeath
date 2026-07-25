#pragma once

#include "Particles.h"

#include "../../../engine/util/MathUtil.h"

namespace StickDeath
{
    class ArcParticles : public Particles
    {
    public:
        ArcParticles(
            const std::string &texture,
            const GameEngine::PointF &origin,
            const GameEngine::PointF &randomizeOrigin,
            const float velocity,
            const float randomizeVelocity,
            const GameEngine::Util::AngleUnit angleUnit,
            const float _startAngle,
            const float _endAngle,
            const float destroyTime,
            const int count,
            const bool doCollision,
            const bool doGravity);
    };
}