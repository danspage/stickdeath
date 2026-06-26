#include "Particles.h"

#include <cmath>

#include "../../../framework/util/MathUtil.h"

#include "../../../framework/graphics/camera/Camera.h"
#include "../../../framework/graphics/Images.h"
#include "../map/Map.h"


namespace StickDeath
{
    void Particle::Update(float speed, float deltaTime)
    {
        position += delta * speed * deltaTime;
    }

    void Particle::Render() const
    {
        GameEngine::PointI screenPos = StickDeath::Camera::WorldToScreen(position);
        GameEngine::DrawImage("sprites/particle/" + texture, screenPos.x, screenPos.y);
    }

    Particles::Particles(const std::string &texture, const GameEngine::PointF &origin, const GameEngine::PointF &delta, const GameEngine::PointF &randomOffset, float speed, int count)
        : texture(texture), origin(origin), delta(delta), randomOffset(randomOffset), speed(speed), count(count), timeSinceBirth(0.0f)
    {
        const GameEngine::PointF originWorld(
            origin.x * StickDeath::Map::TILE_SIZE_VOXELS,
            origin.y * StickDeath::Map::TILE_SIZE_VOXELS);

        const GameEngine::PointF deltaWorld(
            delta.x * StickDeath::Map::TILE_SIZE_VOXELS,
            delta.y * StickDeath::Map::TILE_SIZE_VOXELS);

        const GameEngine::PointF randomOffsetWorld(
            randomOffset.x * StickDeath::Map::TILE_SIZE_VOXELS,
            randomOffset.y * StickDeath::Map::TILE_SIZE_VOXELS);

        destroyTime = std::sqrt(deltaWorld.x * deltaWorld.x + deltaWorld.y * deltaWorld.y) / speed;

        for (int i = 0; i < count; i++)
        {
            float randAngle = GameEngine::Util::RandomFloat(0, M_PI * 2);
            GameEngine::PointF randDelta = GameEngine::PointF(std::cosf(randAngle), std::sinf(randAngle));

            GameEngine::PointF randOrigin = GameEngine::PointF(
                GameEngine::Util::RandomFloat(
                    originWorld.x - randomOffsetWorld.x,
                    originWorld.x + randomOffsetWorld.x),
                GameEngine::Util::RandomFloat(
                    originWorld.y - randomOffsetWorld.y,
                    originWorld.y + randomOffsetWorld.y));

            particles.emplace_back(texture, randOrigin, randDelta);
        }
    }

    void Particles::Update(float deltaTime)
    {
        timeSinceBirth += deltaTime;

        if (timeSinceBirth >= destroyTime)
        {
            Destroy();
            return;
        }

        for (Particle &p : particles)
        {
            p.Update(speed, deltaTime);
        }
    }

    void Particles::Render()
    {
        for (Particle &p : particles)
        {
            p.Render();
        }
    }

    void Particles::Destroy()
    {
        particles.clear();
    }
}