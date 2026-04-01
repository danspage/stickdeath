#include "Collider.h"

namespace StickDeath::Physics
{
    AABB Collider::GetBoundsAt(float x, float y) const
    {
        AABB bounds;
        if (anchoredBottomCenter)
        {
            float halfWidth = width / 2.0f;
            bounds.leftBound = x - halfWidth;
            bounds.rightBound = x + halfWidth;
        }
        else
        {
            bounds.leftBound = x;
            bounds.rightBound = x + width;
        }

        bounds.bottomBound = y;
        bounds.topBound = y + height;

        return bounds;
    }

    TileRange Collider::GetTileRange()
    {
        AABB bounds = GetBounds();

        return {
            static_cast<int>(std::floor(bounds.leftBound)),
            static_cast<int>(std::floor(bounds.rightBound - Map::EPSILON)),
            static_cast<int>(std::floor(bounds.bottomBound)),
            static_cast<int>(std::floor(bounds.topBound - Map::EPSILON)),
        };
    }

    void Collider::DoCollision(float dt)
    {
        // Resolve against tile faces using the collider's own local bounds offsets,
        // so this works for both center-anchored and left-anchored colliders.
        const AABB localBounds = GetBoundsAt(0.0f, 0.0f);
        const float leftOffset = localBounds.leftBound;
        const float rightOffset = localBounds.rightBound;
        const float bottomOffset = localBounds.bottomBound;
        const float topOffset = localBounds.topBound;

        lastXPos = xPos;
        lastYPos = yPos;

        // Reset grounded state each frame
        onGround = false;

        // Use substeps for collision checks
        float remainingDt = dt;
        constexpr float MAX_PHYSICS_STEP = 1.0f / 120.0f;

        while (remainingDt > 0.0f)
        {
            float stepDt = std::min(remainingDt, MAX_PHYSICS_STEP);
            remainingDt -= stepDt;

            // Gravity
            if (doGravity)
            {
                yVel += Map::GRAVITY * stepDt;
            }

            float dx = xVel * stepDt;
            float dy = yVel * stepDt;

            // Horizontal check
            Physics::AABB futureX = GetBoundsAt(xPos + dx, yPos);
            if (xVel > 0)
            {
                bool collided = Map::CheckSolidBlocksExistInColumn(
                    std::floor(futureX.rightBound - Map::EPSILON),
                    std::floor(futureX.bottomBound),
                    std::floor(futureX.topBound - Map::EPSILON));
                if (collided)
                {
                    int tileX = static_cast<int>(std::floor(futureX.rightBound - Map::EPSILON));
                    xPos = tileX - rightOffset;
                    xVel = 0;
                }
                else
                {
                    xPos += dx;
                }
            }
            else if (xVel < 0)
            {
                bool collided = Map::CheckSolidBlocksExistInColumn(
                    std::floor(futureX.leftBound),
                    std::floor(futureX.bottomBound),
                    std::floor(futureX.topBound - Map::EPSILON));
                if (collided)
                {
                    int tileX = static_cast<int>(std::floor(futureX.leftBound));
                    xPos = tileX + 1.0f - leftOffset;
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
                bool collided = Map::CheckSolidBlocksExistInRow(
                    std::floor(futureY.topBound - Map::EPSILON),
                    std::floor(futureY.leftBound),
                    std::floor(futureY.rightBound - Map::EPSILON));
                if (collided)
                {
                    int tileY = static_cast<int>(std::floor(futureY.topBound - Map::EPSILON));
                    yPos = tileY - topOffset;
                    yVel = 0;
                }
                else
                {
                    yPos += dy;
                }
            }
            else if (yVel < 0)
            {
                bool collided = Map::CheckSolidBlocksExistInRow(
                    std::floor(futureY.bottomBound),
                    std::floor(futureY.leftBound),
                    std::floor(futureY.rightBound - Map::EPSILON));
                if (collided)
                {
                    int tileY = static_cast<int>(std::floor(futureY.bottomBound));
                    yPos = tileY + 1.0f - bottomOffset;
                    yVel = 0.0f;

                    onGround = true;
                }
                else
                {
                    yPos += dy;
                }
            }
        }
    }
}