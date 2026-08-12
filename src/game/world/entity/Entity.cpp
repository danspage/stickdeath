#include "Entity.h"

#include "../../../engine/physics/AABB.h"

#include <vector>

namespace StickDeath
{
    void Entity::Update(float dt)
    {
        std::vector<const GameEngine::Physics::AABB *> tileBounds;

        for (Tile *tile : GetTilesInArea(collider.GetBounds()))
        {
            tileBounds.push_back(&tile->GetCollider()->GetCollider()->GetBounds());
        }

        collider.MoveAndDoCollision(dt, tileBounds);
    }
}