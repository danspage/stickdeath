#include "Particles.h"

#include "../../../framework/graphics/Images.h"
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
}