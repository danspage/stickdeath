#pragma once

#include <cstdint>
#include <cmath>

namespace StickDeath
{
    struct EntitySize
    {
        uint16_t width;
        uint16_t height;
    };

    class Entity
    {
    public:
        Entity(EntitySize _size)
        {
            size = _size;
        };

        float GetXPos() { return xPos; }
        float GetYPos() { return yPos; }
        float GetXVel() { return xVel; }
        float getYVel() { return yVel; }
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
        int GetWidth() { return size.width; }
        int GetHeight() { return size.height; }
        int GetTileToLeftOfEntity();
        int GetTileToRightOfEntity();
        int GetTileAboveEntity();
        int GetTileBelowEntity();

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