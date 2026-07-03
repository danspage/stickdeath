#pragma once

#include "Particles.h"

namespace StickDeath
{
    class CircleParticles : public Particles
    {
    public:
        CircleParticles(
            const std::string &texture,
            const GameEngine::PointF &origin,
            const GameEngine::PointF &randomizeOrigin,
            const float velocity,
            const float randomizeVelocity,
            const float destroyTime,
            const int count,
            const bool doCollision,
            const bool doGravity);
    };
}
