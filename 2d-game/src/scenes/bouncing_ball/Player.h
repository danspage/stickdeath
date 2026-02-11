#pragma once

#include "../../Graphics.h"
#include "RectBlock.h"

class Player
{
public:
    Player() {};
    float getXPos() { return xPos; }
    float getYPos() { return yPos; }
    float getXVel() { return xVel; }
    float getYVel() { return yVel; }
    void setXPos(float _xPos) { xPos = _xPos; }
    void setYPos(float _yPos) { yPos = _yPos; }
    void setXVel(float _xVel) { xVel = _xVel; }
    void setYVel(float _yVel) { yVel = _yVel; }
    float getWidth() { return 9; }
    float getHeight() { return 22; }
    std::pair<float, float> getCenter() { return {xPos, yPos + getHeight() / 2}; }
    void moveLeft(double dt);
    void moveRight(double dt);
    void moveUp(double dt);
    void moveDown(double dt);
    bool isColliding(RectBlock *block);
    void doCollision(RectBlock *block);
    void update(double dt);
    void render(Graphics *g);

private:
    float xPos = 0.0;
    float yPos = 0.0;
    float lastXPos = 0.0;
    float lastYPos = 0.0;
    float xVel = 0.0;
    float yVel = 0.0;
    bool facingRight = true;
    float speed = 30.0;
};