#include "Particles.h"

#include "../../../engine/graphics/Images.h"
#include "../../../engine/graphics/camera/Camera.h"

#include <cmath>

namespace StickDeath
{
    Particle::Particle(GameEngine::PointF position, GameEngine::PointF velocity, GameEngine::PointF size, bool doCollision, bool doGravity)
        : doCollision(doCollision), collider(position.x, position.y, size.x, size.y, true)
    {
        collider.SetVel(velocity.x, velocity.y);

        if (doGravity)
            collider.EnableGravity();
    }

    void Particle::Update(float dt)
    {
        if (doCollision)
        {
            const float prevXVel = collider.GetXVel();
            const float prevYVel = collider.GetYVel();

            collider.MoveAndDoCollision(dt);

            constexpr float RESTITUTION_X = 0.6f;
            constexpr float RESTITUTION_Y = 0.45f;
            constexpr float MIN_BOUNCE_SPEED = 1.0f;

            // Bounce if xVel meets min bounce speed and the particle just hit a horizontal wall
            if (std::abs(prevXVel) > MIN_BOUNCE_SPEED && std::abs(collider.GetXVel()) <= Map::EPSILON)
            {
                collider.SetXVel(prevXVel * -RESTITUTION_X);

                // Slight damping on other axis from friction
                collider.SetYVel(collider.GetYVel() * 0.9);
            }

            // Bounce if yVel meets min bounce speed and the particle just hit a vertical wall
            if (std::abs(prevYVel) > MIN_BOUNCE_SPEED && std::abs(collider.GetYVel()) <= Map::EPSILON)
            {
                collider.SetYVel(prevYVel * -RESTITUTION_Y);

                // Slight damping on other axis from friction
                collider.SetXVel(collider.GetXVel() * 0.9);
            }
        }
        else
        {
            collider.MoveWithoutCollision(dt);
        }
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
            const GameEngine::PointF size = GetSize();

            const GameEngine::PointF worldTopLeft = {
                p.collider.GetXPos() * StickDeath::Map::TILE_SIZE_VOXELS - (size.x / 2.0f),
                p.collider.GetYPos() * StickDeath::Map::TILE_SIZE_VOXELS + static_cast<float>(size.y),
            };
            GameEngine::PointI screenPos = StickDeath::Camera::WorldToScreen(worldTopLeft);
            GameEngine::DrawImage(texture, screenPos.x, screenPos.y);
        }
    }

    void Particles::Destroy()
    {
        particles.clear();
    }
}