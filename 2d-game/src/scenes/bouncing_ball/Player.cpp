#include "Player.h"

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

void Player::moveUp(double dt)
{
    yPos -= dt*speed;
}

void Player::moveDown(double dt)
{
    yPos += dt*speed;
}

bool Player::isColliding(RectBlock *block)
{
    if (block->getX() < xPos + getWidth() && block->getX() + block->getWidth() > xPos &&
        block->getY() < yPos + getHeight() && block->getY() + block->getHeight() > yPos)
    {
        return true;
    }
    return false;
}

void Player::doCollision(RectBlock *block)
{
    
}

void Player::update(double dt)
{
    
}