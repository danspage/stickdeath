#include "Entity.h"

namespace StickDeath
{
    Physics::AABB Entity::GetBounds() const
    {
        Physics::AABB bounds;
        bounds.leftBound = xPos - GetWidthBlocks() / 2;
        bounds.rightBound = xPos + GetWidthBlocks() / 2;
        bounds.bottomBound = yPos;
        bounds.topBound = yPos + GetHeightBlocks();
        return bounds;
    }

    Physics::AABB Entity::GetBoundsAt(float x, float y) const
    {
        Physics::AABB bounds;
        bounds.leftBound = x - GetWidthBlocks() / 2;
        bounds.rightBound = x + GetWidthBlocks() / 2;
        bounds.bottomBound = y;
        bounds.topBound = y + GetHeightBlocks();
        return bounds;
    }

    Physics::TileRange Entity::GetOverlappedTiles() const
    {
        Physics::AABB bounds = GetBounds();

        return {
            static_cast<int>(std::floor(bounds.leftBound)),
            static_cast<int>(std::floor(bounds.rightBound - Map::EPSILON)),
            static_cast<int>(std::floor(bounds.bottomBound)),
            static_cast<int>(std::floor(bounds.topBound - Map::EPSILON)),
        };
    }

    void Entity::DoCollision(float dt)
    {
        float dx = xVel * dt;
        float dy = yVel * dt;
        float halfWidth = GetWidthBlocks() / 2.0f;
        float height = GetHeightBlocks();

        // Horizontal check
        Physics::AABB futureX = GetBoundsAt(xPos + dx, yPos);
        if (xVel > 0)
        {
            bool collided = Map::CheckSolidBlocksExistInColumn(floor(futureX.rightBound - Map::EPSILON), floor(futureX.bottomBound), floor(futureX.topBound - Map::EPSILON));
            if (collided)
            {
                int tileX = static_cast<int>(std::floor(futureX.rightBound - Map::EPSILON));
                xPos = tileX - halfWidth;
                xVel = 0;
            }
            else
            {
                xPos += dx;
            }
        }
        else if (xVel < 0)
        {
            bool collided = Map::CheckSolidBlocksExistInColumn(floor(futureX.leftBound), floor(futureX.bottomBound), floor(futureX.topBound - Map::EPSILON));
            if (collided)
            {
                int tileX = static_cast<int>(std::floor(futureX.leftBound));
                xPos = tileX + 1.0f + halfWidth;
                xVel = 0.0f;
            }
            else
            {
                xPos += dx;
            }
        }

        // Vertical check
        Physics::AABB futureY = GetBoundsAt(xPos, yPos + dy);
        if (yVel > 0)
        {
            bool collided = Map::CheckSolidBlocksExistInRow(floor(futureY.topBound - Map::EPSILON), floor(futureY.leftBound), floor(futureY.rightBound - Map::EPSILON));
            if (collided)
            {
                int tileY = static_cast<int>(std::floor(futureY.topBound - Map::EPSILON));
                yPos = tileY - height;
                yVel = 0;
            }
            else
            {
                yPos += dy;
            }
        }
        else if (yVel < 0)
        {
            bool collided = Map::CheckSolidBlocksExistInRow(floor(futureY.bottomBound), floor(futureY.leftBound), floor(futureY.rightBound - Map::EPSILON));
            if (collided)
            {
                int tileY = static_cast<int>(std::floor(futureY.bottomBound));
                yPos = tileY + 1.0f;
                yVel = 0.0f;
            }
            else
            {
                yPos += dy;
            }
        }
    }
}