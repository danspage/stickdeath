#pragma once

#include <string>
#include <vector>

#include "../../physics/AABB.h"
#include "../../../../engine/util/Timer.h"

namespace StickDeath
{
    class Entity;

    struct TileProperties
    {
        std::string id;

        std::vector<std::string> texturePaths;

        bool isSolid;
        std::vector<Physics::AABB> bounds;

        // For animated tiles, these will be set to point to the actual animation data stored in the TileDefinition for this tile, so that when the animation updates it can update the current frame for all tiles that use that animation at once. For non-animated tiles, these will just be null pointers.
        bool animated = false;
    };

    class Tile
    {
    public:
        Tile(int xPos, int yPos, std::string tileName);

        void HardOverwriteCoordinates(int xPos, int yPos);

        TileProperties GetProperties() const;

        virtual void Render();
        virtual void Update(float dt) {}
        virtual void OnCollision(Entity *entity, bool isInside) {};

    protected:
        int x = 0, y = 0;
        TileProperties properties;
    };
}