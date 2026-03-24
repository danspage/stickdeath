#pragma once

#include <string>

namespace StickDeath
{
    class Block
    {
    public:
        Block(int xPos, int yPos, std::string blockName);

        void Render();
        void Update(float dt);
    private:
        std::string texturePath;
        int x, y;
    };
}