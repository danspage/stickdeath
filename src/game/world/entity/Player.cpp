#include "Player.h"

namespace StickDeath
{
    void Player::HandleKeyPress(int key)
    {
        if (key == KEY_UP && GetCollider()->IsOnGround())
        {
            // Jump
            GetCollider()->SetYVel(15);
        }
    }

    void Player::Update(float dt)
    {
        playerAnim.UpdateAnimation(dt);

        if (IsKeyDown(KEY_LEFT))
        {
            playerAnim.SetAnimationActive(true);
            facingLeft = true;
            GetCollider()->SetXVel(-speed);
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            playerAnim.SetAnimationActive(true);
            facingLeft = false;
            GetCollider()->SetXVel(speed);
        }
        else
        {
            playerAnim.SetAnimationActive(false);
            GetCollider()->SetXVel(0);
        }

        GetCollider()->DoCollision(dt);
    }

    void Player::Render()
    {
        float worldX = GetCollider()->GetXPos() * StickDeath::Map::TILE_SIZE;
        float worldY = GetCollider()->GetYPos() * StickDeath::Map::TILE_SIZE;

        int drawX = static_cast<int>(std::floor(worldX - WIDTH_PX / 2.0f));
        int drawY = static_cast<int>(std::floor(GameEngine::HEIGHT_VOXELS - worldY - HEIGHT_PX));

        GameEngine::DrawImage(
            playerAnim.GetCurrentFrame(),
            drawX,
            drawY,
            {.flipHorizontal = facingLeft});
    }
}