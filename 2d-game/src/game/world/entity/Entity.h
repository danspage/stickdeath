#pragma once

#include <cstdint>
#include <cmath>

#include "../map/Map.h"
#include "../physics/AABB.h"

namespace StickDeath
{
    struct EntitySize
    {
        uint16_t widthPx;
        uint16_t heightPx;
    };

    class Entity
    {
    public:
        Entity(EntitySize _size)
        {
            size = _size;
            
        };

        float GetXPos() const { return xPos; }
        float GetYPos() const { return yPos; }
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
        float GetWidthBlocks() const { return (float)size.widthPx / (float)StickDeath::Map::TILE_SIZE; }
        float GetHeightBlocks() const { return (float)size.heightPx / (float)StickDeath::Map::TILE_SIZE; }
        int GetWidthPixels() const { return size.widthPx; }
        int GetHeightPixels() const { return size.heightPx; }

        Physics::AABB GetBounds() const;
        Physics::AABB GetBoundsAt(float x, float y) const;
        Physics::TileRange GetOverlappedTiles() const;

        void DoCollision(float dt);
        virtual void Render() {};
        virtual void Update(float dt) {};

    private:
        float xPos = 0.0;
        float yPos = 0.0;
        float lastXPos = 0.0;
        float lastYPos = 0.0;
        float xVel = 0.0;
        float yVel = 0.0;
        EntitySize size;
    };
}