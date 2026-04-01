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
        Entity(float x, float y, float width, float height, bool anchoredBottomCenter)
            : collider(x, y, width, height, anchoredBottomCenter)
        {
        }

        Physics::Collider *GetCollider() { return &collider; }
        virtual void Render() {};
        virtual void Update(float dt) { collider.DoCollision(dt); }

    private:
        Physics::Collider collider;
    };
}