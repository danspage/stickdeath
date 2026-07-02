#pragma once

#include <vector>
#include <string>

#include "../../../framework/graphics/GameImage.h"
#include "../../../framework/basic_types/Positional.h"
#include "../physics/Collider.h"

namespace StickDeath
{
    // INDIVIDUAL PARTICLE
    class Particle
    {
    public:
        Particle(GameEngine::PointF position, GameEngine::PointF velocity, GameEngine::PointF size, bool doCollision, bool doGravity);

        void Update(float dt);

        /// @brief Whether the particle will collide with other physics objects.
        bool doCollision;

        /// @brief The collider used to link the particle with the physics engine.
        Physics::Collider collider;
    };

    // BASE PARTICLES CONTROLLER CLASS
    class Particles
    {
    public:
        Particles(const std::string &texture, const GameEngine::PointF &origin, const GameEngine::PointF &randomizeOrigin, const float destroyTime, const int count);

        void Update(float dt);
        void Render();
        void Destroy();

        std::vector<Particle> particles;

    private:
        const std::string texture;
        GameEngine::GameImage *textureImage;

        const GameEngine::PointF origin;
        const GameEngine::PointF randomizeOrigin;

        float timeSinceBirth;
        const float destroyTime;

        const int count;
    };

    // CIRCLE PARTICLES

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
