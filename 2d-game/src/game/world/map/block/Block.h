#pragma once

#include <string>

#include "../../physics/AABB.h"

namespace StickDeath
{
    struct BlockProperties
    {
        bool isSolid;
    };

    class Block
    {
    public:
        Block(int xPos, int yPos, std::string blockName);

        void HardOverwriteCoordinates(int xPos, int yPos);

        Physics::AABB GetBounds() const;

        BlockProperties GetProperties() const;
        
        void Render();
        virtual void Update(float dt) {}
    private:
        std::string texturePath;
        int x, y;
        BlockProperties properties;
    };
}