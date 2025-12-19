#include "../Graphics.h"

class Player
{
public:
    Player() {};
    float getXPos();
    float getYPos();
    float getXVel();
    float getYVel();
    void setXPos(float _xPos);
    void setYPos(float _yPos);
    void setXVel(float _xVel);
    void setYVel(float _yVel);
    void render(Graphics* g);
    void moveLeft(double dt);
    void moveRight(double dt);
private:
    float xPos = 0.0;
    float yPos = 50.0;
    float xVel = 0.0;
    float yVel = 0.0;
    bool facingRight = true;
    float speed = 30.0;
};