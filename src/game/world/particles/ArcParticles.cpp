#include "ArcParticles.h"
#include "Particles.h"

namespace StickDeath
{
    ArcParticles::ArcParticles(
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
        const bool doGravity) : Particles(texture, origin, randomizeOrigin, destroyTime, count)
    {
        // Make sure we're using radians for the algorithm
        float startAngle =
            (angleUnit == GameEngine::Util::AngleUnit::Degrees)
                ? GameEngine::Util::DegreesToRadians(_startAngle)
                : _startAngle;
        float endAngle =
            (angleUnit == GameEngine::Util::AngleUnit::Degrees)
                ? GameEngine::Util::DegreesToRadians(_endAngle)
                : _endAngle;

        for (int i = 0; i < count; i++)
        {
            float randAngle = GameEngine::Util::RandomFloat(startAngle, endAngle);

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