#pragma once

#include <cstdint>
#include <cmath>
#include <string>

#include "../map/Map.h"
#include "../map/tile/Tiles.h"
#include "../../../engine/physics/Collider.h"
#include "../../../engine/basic_types/Positional.h"

namespace StickDeath
{
    class Entity
    {
    public:
        Entity(std::string id, float x, float y, float width, float height, bool anchoredBottomCenter)
            : id(id), collider(x, y, width, height, anchoredBottomCenter)
        {
        }

        GameEngine::Physics::Collider *GetCollider() { return &collider; }

        std::string GetID() const { return id; }
        void SetX(float x) { collider.SetXPos(x); }
        void SetY(float y) { collider.SetYPos(y); }
        void SetPos(float x, float y) { collider.SetPos(x, y); }
        float GetX() const { return collider.GetXPos(); }
        float GetY() const { return collider.GetYPos(); }
        GameEngine::PointF GetPos() { return {collider.GetXPos(), collider.GetYPos()}; }
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

        void Update(float dt);

    private:
        const std::string id;
        GameEngine::Physics::Collider collider;
    };
}