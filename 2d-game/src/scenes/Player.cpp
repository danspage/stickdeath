#include "Player.h"

float Player::getXPos() { return xPos; }
float Player::getYPos() { return yPos; }
float Player::getXVel() { return xVel; }
float Player::getYVel() { return yVel; }
void Player::setXPos(float _xPos) { xPos = _xPos; }
void Player::setYPos(float _yPos) { yPos = _yPos; }
void Player::setXVel(float _xVel) { xVel = _xVel; }
void Player::setYVel(float _yVel) { yVel = _yVel; }

void Player::render(Graphics* g)
{
    if (facingRight)
    {
        g->DrawImage("player_right", ((int)xPos)-4, (int)yPos, false, false);
    }
    else
    {
        g->DrawImage("player_left", ((int)xPos)-4, (int)yPos, false, false);
    }
}

void Player::moveLeft(double dt)
{
    xPos -= dt*speed;
    facingRight = false;
}

void Player::moveRight(double dt)
{
    xPos += dt*speed;
    facingRight = true;
}