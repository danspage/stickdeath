#pragma once

#include "AABB.h"
#include "../map/Map.h"

namespace StickDeath::Physics
{
    class Collider
    {
    private:
        float xPos;
        float yPos;
        float lastXPos = 0.0;
        float lastYPos = 0.0;
        float xVel = 0.0;
        float yVel = 0.0;
        float width;
        float height;
        bool onGround = false;
        bool doGravity = false;
        bool anchoredBottomCenter;

    public:
        Collider(float x, float y, float width, float height, bool anchoredBottomCenter)
            : xPos(x), yPos(y), width(width), height(height), anchoredBottomCenter(anchoredBottomCenter)
        {
        }

        AABB GetBoundsAt(float x, float y) const;
        AABB GetBounds() const { return GetBoundsAt(xPos, yPos); }
        TileRange GetTileRange();

        float GetXPos() const { return xPos; }
        float GetYPos() const { return yPos; }
        float GetWidth() const { return width; }
        float GetHeight() const { return height; }
        float GetXVel() const { return xVel; }
        float GetYVel() const { return yVel; }
        void SetXPos(float _xPos) { xPos = _xPos; }
        void SetYPos(float _yPos) { yPos = _yPos; }
        void SetPos(float _xPos, float _yPos)
        {
            xPos = _xPos;
            yPos = _yPos;
        }
        void SetXVel(float _xVel) { xVel = _xVel; }
        void SetYVel(float _yVel) { yVel = _yVel; }
        void SetVel(float _xVel, float _yVel)
        {
            xVel = _xVel;
            yVel = _yVel;
        }
        bool IsOnGround() const { return onGround; }
        void EnableGravity() { doGravity = true; }
        void DisableGravity() { doGravity = false; }

        void DoCollision(float dt);
    };
}