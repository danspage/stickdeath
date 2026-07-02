#include "Particles.h"

#include "../../../framework/graphics/Images.h"
#include "../../../framework/util/MathUtil.h"
#include "../../../framework/graphics/camera/Camera.h"

namespace StickDeath
{
    Particle::Particle(GameEngine::PointF position, GameEngine::PointF velocity, GameEngine::PointF size, bool doCollision, bool doGravity) : doCollision(doCollision),
                                                                                                                                              collider(position.x, position.y, size.x, size.y, true)
    {
        collider.SetVel(velocity.x, velocity.y);

        if (doGravity)
            collider.EnableGravity();
    }

    void Particle::Update(float dt)
    {
        if (doCollision)
        {
            collider.MoveAndDoCollision(dt);
        }
        else
        {
            collider.MoveWithoutCollision(dt);
        }
    }

    Particles::Particles(const std::string &texture, const GameEngine::PointF &origin, const GameEngine::PointF &randomizeOrigin, const float destroyTime, const int count)
        : texture(texture), origin(origin), randomizeOrigin(randomizeOrigin), destroyTime(destroyTime), count(count), timeSinceBirth(0.0f)
    {
        textureImage = GameEngine::GetImage("sprites/particle/" + texture);
    }

    void Particles::Update(float dt)
    {
        timeSinceBirth += dt;
        if (timeSinceBirth >= destroyTime)
        {
            particles.clear();
            return;
        }

        for (Particle &p : particles)
        {
            p.Update(dt);
        }
    }

    void Particles::Render()
    {
        for (Particle &p : particles)
        {
            const GameEngine::PointF worldTopLeft = {
                p.collider.GetXPos() * StickDeath::Map::TILE_SIZE_VOXELS - (textureImage->getWidth() / 2.0f),
                p.collider.GetYPos() * StickDeath::Map::TILE_SIZE_VOXELS + static_cast<float>(textureImage->getHeight()),
            };
            GameEngine::PointI screenPos = StickDeath::Camera::WorldToScreen(worldTopLeft);
            GameEngine::DrawImage(textureImage, screenPos.x, screenPos.y);
        }
    }

    void Particles::Destroy()
    {
        particles.clear();
    }

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
        GameEngine::GameImage *particleImage = GameEngine::GetImage("sprites/particle/" + texture);

        for (int i = 0; i < count; i++)
        {
            float randAngle = GameEngine::Util::RandomFloat(0, M_PI * 2);

            GameEngine::PointF randDelta = GameEngine::PointF(std::cosf(randAngle) * velocity, std::sinf(randAngle) * velocity);

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
                GameEngine::PointF(
                    static_cast<float>(particleImage->getWidth()) / StickDeath::Map::TILE_SIZE_VOXELS,
                    static_cast<float>(particleImage->getHeight()) / StickDeath::Map::TILE_SIZE_VOXELS),
                doCollision,
                doGravity);
        }
    }
}