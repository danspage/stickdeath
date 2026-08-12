#pragma once

namespace GameEngine::Physics
{
    struct AABB
    {
        float leftBound, rightBound, topBound, bottomBound;

        bool CheckCollision(const AABB &other) const
        {
            return (leftBound < other.rightBound &&
                    rightBound > other.leftBound &&
                    bottomBound < other.topBound &&
                    topBound > other.bottomBound);
        }
    };
}