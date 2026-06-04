#pragma once

#include <string>
#include <vector>

#include "../../physics/AABB.h"

namespace StickDeath
{
    class Entity;

    struct TileProperties
    {
        bool isSolid;
        std::vector<Physics::AABB> bounds;
    };

    class Tile
    {
    public:
        Tile(int xPos, int yPos, std::string tileName);

        void HardOverwriteCoordinates(int xPos, int yPos);

        TileProperties GetProperties() const;

        void Render();
        virtual void Update(float dt) {}
        virtual void OnCollision(Entity *entity, bool isInside) {};

    protected:
        std::string texturePath;
        int x = 0, y = 0;
        TileProperties properties;
    };
}