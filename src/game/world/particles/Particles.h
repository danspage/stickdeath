#pragma once

#include <string>
#include <vector>

#include "../../../framework/basic_types/Positional.h"

namespace StickDeath
{
    class Particle
    {
    public:
        Particle(const std::string &texture, const GameEngine::PointF &position, const GameEngine::PointF &delta)
            : texture(texture), position(position), delta(delta) {}

        /// @brief Updates the particle's position based on its delta and the time elapsed.
        /// @param deltaTime The time elapsed since the last update.
        void Update(float speed, float deltaTime);

        /// @brief Renders the particle to the screen.
        void Render() const;

    private:
        /// @brief The particle texture being used, relative to `images/sprites/particles`.
        std::string texture;

        /// @brief The position of the particle in the world.
        GameEngine::PointF position;

        /// @brief The delta in each direction the particle will move over time, this will be determined upon creation given the particles speed and a random angle from the origin
        GameEngine::PointF delta;
    };

    class Particles
    {
    public:
        /// @brief Creates a particle emitter.
        /// @param texture Particle texture name under assets/images/sprites/particle.
        /// @param origin Origin in tile coordinates (supports fractional tile positions).
        /// @param delta Spread distance in tile units.
        /// @param randomOffset Random spawn offset in tile units.
        /// @param speed Particle movement speed in world voxels per second.
        /// @param count Number of particles to spawn.
        Particles(const std::string &texture, const GameEngine::PointF &origin, const GameEngine::PointF &delta, const GameEngine::PointF &randomOffset, float speed, int count);

        /// @brief Updates the particles' positions based on their deltas and the time elapsed.
        /// @param deltaTime The time elapsed since the last update.
        void Update(float deltaTime);

        /// @brief Renders the particles to the screen.
        void Render();

        /// @brief Destroys the particles, clearing them from memory.
        void Destroy();

    private:
        /// @brief The particle texture being used, relative to `images/sprites/particles`.
        std::string texture;

        /// @brief The emitter origin in tile coordinates.
        GameEngine::PointF origin;

        /// @brief How far in each direction from the origin the particles will spread, in tile units.
        GameEngine::PointF delta;

        /// @brief An optional random offset applied relative to the origin when each particle is created, in tile units.
        GameEngine::PointF randomOffset;

        /// @brief The speed at which the particles will move from the origin to the delta.
        float speed;

        /// @brief The number of particles that will be created.
        int count;

        /// @brief How many seconds the particles have existed for, used to destroy itself once the allotted time has elapsed.
        float timeSinceBirth;

        /// @brief How much time must pass for the particles to be destroyed. Calculated based on the delta and speed.
        float destroyTime;

        /// @brief A vector of particle objects that will be updated and rendered.
        std::vector<Particle> particles;
    };
}