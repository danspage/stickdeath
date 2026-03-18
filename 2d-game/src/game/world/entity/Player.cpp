#include "Player.h"

void Player::Update(float dt)
{
    playerAnim.UpdateAnimation(dt);

    if (IsKeyDown(KEY_LEFT))
    {
        playerAnim.SetAnimationActive(true);
        facingLeft = true;
        SetXPos(GetXPos() - dt*speed);
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        playerAnim.SetAnimationActive(true);
        facingLeft = false;
        SetXPos(GetXPos() + dt*speed);
    }
    else
    {
        playerAnim.SetAnimationActive(false);
    }
}

void Player::Render()
{
    GameEngine::DrawImage(playerAnim.GetCurrentFrame(), std::floor(GetXPos()) - (GetWidth() / 2), std::floor(GetYPos() - GetHeight()), {.flipHorizontal = facingLeft});
}