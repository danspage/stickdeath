#pragma once

#include <string>
#include <vector>

#include "../../../../engine/physics/AABB.h"
#include "../../../../engine/physics/Collider.h"
#include "../../../../engine/util/Timer.h"
#include "Tiles.h"

namespace StickDeath
{
    class Entity;

    class TileCollider
    {
    public:
        TileCollider(float x, float y, float width, float height, bool anchoredBottomCenter, Tile *tile)
            : owner(tile),
              collider(GameEngine::Physics::Collider(x, y, width, height, anchoredBottomCenter))
        {
        }

        const GameEngine::Physics::Collider* GetCollider() { return &collider; }

        Tile *owner = nullptr;

    private:
        GameEngine::Physics::Collider collider;
    };

    struct TileProperties
    {
        std::string id;

        std::string texture;

        std::map<std::string, TileAnimationState> animationStates = {};

        bool isSolid;
        std::vector<GameEngine::Physics::AABB> bounds;

        // For animated tiles, these will be set to point to the actual animation data stored in the TileDefinition for this tile, so that when the animation updates it can update the current frame for all tiles that use that animation at once. For non-animated tiles, these will just be null pointers.
        bool animated = false;
    };

    class Tile
    {
    public:
        Tile(int xPos, int yPos, std::string tileName);

        void HardOverwriteCoordinates(int xPos, int yPos);

        TileProperties GetProperties() const;

        TileCollider *GetCollider() { return &tileCollider; }

        virtual void Render();
        virtual void Update(float dt) {}
        virtual void OnCollision(Entity *entity, bool isInside) {};

    protected:
        int x = 0, y = 0;
        TileProperties properties;
        TileCollider tileCollider;
    };
}