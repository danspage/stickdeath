#pragma once

#include <string>
#include <vector>

#include "../../physics/AABB.h"

namespace StickDeath
{
    class Entity;
    
    struct BlockProperties
    {
        bool isSolid;
        std::vector<Physics::AABB> bounds;
    };

    class Block
    {
    public:
        Block(int xPos, int yPos, std::string blockName);

        void HardOverwriteCoordinates(int xPos, int yPos);

        BlockProperties GetProperties() const;
        
        void Render();
        virtual void Update(float dt) {}
        virtual void OnCollision(Entity* entity, bool isInside) {};
    protected:
        std::string texturePath;
        int x = 0, y = 0;
        BlockProperties properties;
    };
}