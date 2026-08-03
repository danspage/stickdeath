#pragma once

#include <vector>
#include <string>

#include "../../../engine/graphics/Images.h"
#include "../../../engine/graphics/GameImage.h"
#include "../../../engine/basic_types/Positional.h"
#include "../physics/Collider.h"
#include "../../../engine/graphics/textures/TextureManager.h";

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
        Particles(
            const std::string &texture,
            const GameEngine::PointF &origin,
            const GameEngine::PointF &randomizeOrigin,
            const float destroyTime,
            const int count)
            : texture("sprites/particle/" + texture),
              origin(origin),
              randomizeOrigin(randomizeOrigin),
              destroyTime(destroyTime),
              count(count),
              timeSinceBirth(0.0f)
        {
        }

        void Update(float dt);
        void Render();
        void Destroy();

        inline GameEngine::PointF GetSize()
        {
            const auto &currentFrame = GameEngine::TextureManager::GetTexture(texture);

            return {
                static_cast<float>(currentFrame.getWidth()) / static_cast<float>(Map::TILE_SIZE_VOXELS),
                static_cast<float>(currentFrame.getHeight()) / static_cast<float>(Map::TILE_SIZE_VOXELS),
            };
        }

        std::vector<Particle> particles;

    private:
        const std::string texture;

        const GameEngine::PointF origin;
        const GameEngine::PointF randomizeOrigin;

        float timeSinceBirth;
        const float destroyTime;

        const int count;
    };

}
