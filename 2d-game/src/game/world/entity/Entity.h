#pragma once

class Entity
{
public:
    virtual ~Entity() {};

    float getXPos() { return xPos; }
    float getYPos() { return yPos; }
    float getXVel() { return xVel; }
    float getYVel() { return yVel; }
    void setXPos(float _xPos) { xPos = _xPos; }
    void setYPos(float _yPos) { yPos = _yPos; }
    void setXVel(float _xVel) { xVel = _xVel; }
    void setYVel(float _yVel) { yVel = _yVel; }
private:
    float xPos = 0.0;
    float yPos = 0.0;
    float lastXPos = 0.0;
    float lastYPos = 0.0;
    float xVel = 0.0;
    float yVel = 0.0;
    int width, height;
};