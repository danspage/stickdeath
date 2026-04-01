#pragma once

namespace StickDeath::Physics
{
    struct AABB
    {
        float leftBound, rightBound, topBound, bottomBound;

        bool CheckCollision(AABB &other) const
        {
            return (leftBound < other.rightBound &&
                    rightBound > other.leftBound &&
                    bottomBound < other.topBound &&
                    topBound > other.bottomBound);
        }
    };

    struct TileRange
    {
        int minX, maxX, minY, maxY;
    };
}