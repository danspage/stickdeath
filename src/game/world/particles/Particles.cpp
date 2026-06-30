#include "Particles.h"

#include <cmath>

#include "../../../framework/util/MathUtil.h"

#include "../../../framework/graphics/camera/Camera.h"
#include "../../../framework/graphics/Images.h"
#include "../map/Map.h"

namespace StickDeath
{
    Particle::Particle(const std::string &texture, const GameEngine::PointF &position, const GameEngine::PointF &delta, bool doCollision, bool doGravity)
        : texture(texture), doCollision(doCollision), collider(
            position.x,
            position.y,
            static_cast<float>(GameEngine::GetImage("sprites/particle/" + texture)->getWidth()) / StickDeath::Map::TILE_SIZE_VOXELS,
            static_cast<float>(GameEngine::GetImage("sprites/particle/" + texture)->getHeight()) / StickDeath::Map::TILE_SIZE_VOXELS,
            true)
    {
        collider.SetVel(delta.x, delta.y);

        if (doGravity)
        {
            collider.EnableGravity();
        }
    }

    void Particle::Update(float dt)
    {
        if (doCollision)
            collider.MoveAndDoCollision(dt);
        else
            collider.MoveWithoutCollision(dt);
    }

    void Particle::Render(GameEngine::GameImage *image)
    {
        const GameEngine::PointF worldTopLeft = {
            collider.GetXPos() * StickDeath::Map::TILE_SIZE_VOXELS - (image->getWidth() / 2.0f),
            collider.GetYPos() * StickDeath::Map::TILE_SIZE_VOXELS + static_cast<float>(image->getHeight()),
        };
        GameEngine::PointI screenPos = StickDeath::Camera::WorldToScreen(worldTopLeft);
        GameEngine::DrawImage(image, screenPos.x, screenPos.y);
    }

    Particles::Particles(const std::string &texture, const GameEngine::PointF &origin, const GameEngine::PointF &delta, const GameEngine::PointF &randomOffset, const float speed, const int count, const bool doCollision, const bool doGravity)
        : texture(texture), origin(origin), delta(delta), randomOffset(randomOffset), speed(speed), count(count), timeSinceBirth(0.0f)
    {
        textureImage = GameEngine::GetImage("sprites/particle/" + texture);

        const GameEngine::PointF deltaWorld(
            delta.x * StickDeath::Map::TILE_SIZE_VOXELS,
            delta.y * StickDeath::Map::TILE_SIZE_VOXELS);

        const float speedTilesPerSecond = speed / StickDeath::Map::TILE_SIZE_VOXELS;

        destroyTime = std::sqrt(deltaWorld.x * deltaWorld.x + deltaWorld.y * deltaWorld.y) / speed;

        for (int i = 0; i < count; i++)
        {
            float randAngle = GameEngine::Util::RandomFloat(0, M_PI * 2);
            GameEngine::PointF randDelta = GameEngine::PointF(std::cosf(randAngle) * speedTilesPerSecond, std::sinf(randAngle) * speedTilesPerSecond);

            GameEngine::PointF randOrigin = GameEngine::PointF(
                GameEngine::Util::RandomFloat(
                    origin.x - randomOffset.x,
                    origin.x + randomOffset.x),
                GameEngine::Util::RandomFloat(
                    origin.y - randomOffset.y,
                    origin.y + randomOffset.y));

            particles.emplace_back(texture, randOrigin, randDelta, doCollision, doGravity);
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
            p.Update(deltaTime);
        }
    }

    void Particles::Render()
    {
        for (Particle &p : particles)
        {
            p.Render(textureImage);
        }
    }

    void Particles::Destroy()
    {
        particles.clear();
    }
}