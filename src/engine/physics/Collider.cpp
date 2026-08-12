#include "Collider.h"

#include "../Constants.h";

namespace GameEngine::Physics
{
    constexpr float MAX_PHYSICS_STEP = 1.0f / 120.0f;

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

    void Collider::MoveWithoutCollision(float dt)
    {
        lastXPos = xPos;
        lastYPos = yPos;

        if (doGravity)
        {
            yVel += GameEngine::GRAVITY * dt;
        }

        if (std::abs(xVel) < GameEngine::EPSILON)
            xVel = 0;
        if (std::abs(yVel) < GameEngine::EPSILON)
            yVel = 0;

        xPos += xVel * dt;
        yPos += yVel * dt;
    }

    std::vector<CollisionHit> Collider::MoveAndDoCollision(float dt, const std::vector<const AABB *> &otherBounds)
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

        while (remainingDt > 0.0f)
        {
            float stepDt = std::min(remainingDt, MAX_PHYSICS_STEP);
            remainingDt -= stepDt;

            // Gravity
            if (doGravity)
            {
                yVel += GameEngine::GRAVITY * stepDt;
            }

            float dx = xVel * stepDt;
            float dy = yVel * stepDt;

            // Horizontal check
            AABB futureX = GetBoundsAt(xPos + dx, yPos);

            if (xVel > 0.0f)
            {
                bool hit = false;

                for (const AABB *other : otherBounds)
                {

                    if (futureX.CheckCollision(*other))
                    {
                        const float contactX = other->leftBound;
                        xPos = contactX - rightOffset;
                        xVel = 0.0f;
                        hit = true;
                        break;
                    }
                }

                if (!hit)
                {
                    xPos += dx;
                }
            }
            else if (xVel < 0.0f)
            {
                bool hit = false;

                for (const AABB *other : otherBounds)
                {
                    if (futureX.CheckCollision(*other))
                    {
                        const float contactX = other->rightBound;
                        xPos = contactX - leftOffset;
                        xVel = 0.0f;
                        hit = true;
                        break;
                    }
                }

                if (!hit)
                {
                    xPos += dx;
                }
            }

            // Vertical check
            AABB futureY = GetBoundsAt(xPos, yPos + dy);

            if (yVel > 0.0f)
            {
                bool hit = false;

                for (const AABB *other : otherBounds)
                {
                    if (futureY.CheckCollision(*other))
                    {
                        const float contactY = other->bottomBound;
                        yPos = contactY - topOffset;
                        yVel = 0.0f;
                        hit = true;
                        break;
                    }
                }

                if (!hit)
                {
                    yPos += dy;
                }
            }
            else if (yVel < 0.0f)
            {
                bool hit = false;

                for (const AABB *other : otherBounds)
                {
                    if (futureY.CheckCollision(*other))
                    {
                        const float contactY = other->topBound;
                        yPos = contactY - bottomOffset;
                        yVel = 0.0f;
                        onGround = true;
                        hit = true;
                        break;
                    }
                }

                if (!hit)
                {
                    yPos += dy;
                }
            }
        }

        std::vector<CollisionHit> hits;

        const AABB selfBounds = GetBounds();

        const int minX = static_cast<int>(std::floor(selfBounds.leftBound));
        const int maxX = static_cast<int>(std::floor(selfBounds.rightBound - GameEngine::EPSILON));
        const int minY = static_cast<int>(std::floor(selfBounds.bottomBound));
        const int maxY = static_cast<int>(std::floor(selfBounds.topBound - GameEngine::EPSILON));

        for (int y = minY; y <= maxY; y++)
        {
            for (int x = minX; x <= maxX; x++)
            {
                for (const AABB *other : otherBounds)
                {
                    // if (!finalBounds.CheckCollision(worldBound))
                    //     continue;

                    // Compute minimum overlap across both axes to determine inside vs touching
                    const float overlapX = std::min(selfBounds.rightBound - other->leftBound,
                                                    other->rightBound - selfBounds.leftBound);
                    const float overlapY = std::min(selfBounds.topBound - other->bottomBound,
                                                    other->topBound - selfBounds.bottomBound);
                    const bool isInside = overlapX > GameEngine::EPSILON && overlapY > GameEngine::EPSILON;

                    if (isInside)
                        hits.push_back({other, isInside});
                }
            }
        }

        if (std::abs(xVel) < GameEngine::EPSILON)
            xVel = 0;
        if (std::abs(yVel) < GameEngine::EPSILON)
            yVel = 0;

        return hits;
    }
}