#pragma once

#include <cstdint>
#include <cmath>

#include "../map/Map.h"
#include "../physics/Collider.h"

namespace StickDeath
{
    class Entity
    {
    public:
        Entity(float x, float y, float widthVoxels, float heightVoxels, bool anchoredBottomCenter)
            : collider(x, y, widthVoxels, heightVoxels, anchoredBottomCenter)
        {
        }

        Physics::Collider *GetCollider() { return &collider; }

        void SetX(float x) { collider.SetXPos(x); }
        void SetY(float y) { collider.SetYPos(y); }
        void SetPos(float x, float y) { collider.SetPos(x, y); }
        float GetX() const { return collider.GetXPos(); }
        float GetY() const { return collider.GetYPos(); }
        float GetWidth() const { return collider.GetWidth(); }
        float GetHeight() const { return collider.GetHeight(); }
        float GetXVel() const { return collider.GetXVel(); }
        float GetYVel() const { return collider.GetYVel(); }
        void SetXVel(float xVel) { collider.SetXVel(xVel); }
        void SetYVel(float yVel) { collider.SetYVel(yVel); }
        void SetVel(float xVel, float yVel) { collider.SetVel(xVel, yVel); }
        bool IsOnGround() const { return collider.IsOnGround(); }
        bool IsAffectedByGravity() const { return collider.IsOnGround(); }
        void EnableGravity() { collider.EnableGravity(); }
        void DisableGravity() { collider.DisableGravity(); }

        virtual void Render() {};
        virtual void Update(float dt) { collider.DoCollision(dt); }

    private:
        Physics::Collider collider;
    };
}