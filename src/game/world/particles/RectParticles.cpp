#include "RectParticles.h"
#include "Particles.h"

#include "../../../engine/graphics/Images.h"

namespace StickDeath
{
    RectParticles::RectParticles(
        const std::string &texture,
        const GameEngine::PointF &minPos,
        const GameEngine::PointF &maxPos,
        const GameEngine::PointF &velocity,
        const GameEngine::PointF &randomizeVelocity,
        const float destroyTime,
        const int count,
        const bool doCollision,
        const bool doGravity) : Particles(texture, minPos, {0, 0}, destroyTime, count)
    {
        for (int i = 0; i < count; i++)
        {
            float x = GameEngine::Util::RandomFloat(minPos.x, maxPos.x);
            float y = GameEngine::Util::RandomFloat(minPos.y, maxPos.y);

            GameEngine::PointF randVelocity = GameEngine::PointF(
                GameEngine::Util::RandomFloat(
                    velocity.x - randomizeVelocity.x,
                    velocity.x + randomizeVelocity.x),
                GameEngine::Util::RandomFloat(
                    velocity.y - randomizeVelocity.y,
                    velocity.y + randomizeVelocity.y));

            GameEngine::PointF randOrigin = GameEngine::PointF(
                GameEngine::Util::RandomFloat(minPos.x, maxPos.x),
                GameEngine::Util::RandomFloat(minPos.y, maxPos.y));

            particles.emplace_back(
                randOrigin,
                randVelocity,
                GetSize(),
                doCollision,
                doGravity);
        }
    }
}