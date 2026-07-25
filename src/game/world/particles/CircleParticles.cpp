#include "CircleParticles.h"

#include "../../../engine/util/MathUtil.h"
#include "../../../engine/graphics/Images.h"

namespace StickDeath
{
    CircleParticles::CircleParticles(
        const std::string &texture,
        const GameEngine::PointF &origin,
        const GameEngine::PointF &randomizeOrigin,
        const float velocity,
        const float randomizeVelocity,
        const float destroyTime,
        const int count,
        const bool doCollision,
        const bool doGravity) : Particles(texture, origin, randomizeOrigin, destroyTime, count)
    {
        for (int i = 0; i < count; i++)
        {
            float randAngle = GameEngine::Util::RandomFloat(0, M_PI * 2);

            float randVelocity = GameEngine::Util::RandomFloat(
                velocity - randomizeVelocity,
                velocity + randomizeVelocity);

            GameEngine::PointF randDelta = GameEngine::PointF(std::cosf(randAngle) * randVelocity, std::sinf(randAngle) * randVelocity);

            GameEngine::PointF randOrigin = GameEngine::PointF(
                GameEngine::Util::RandomFloat(
                    origin.x - randomizeOrigin.x,
                    origin.x + randomizeOrigin.x),
                GameEngine::Util::RandomFloat(
                    origin.y - randomizeOrigin.y,
                    origin.y + randomizeOrigin.y));

            particles.emplace_back(
                randOrigin,
                randDelta,
                GetSize(),
                doCollision,
                doGravity);
        }
    }
}