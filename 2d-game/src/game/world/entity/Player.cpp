#include "Player.h"

namespace StickDeath
{
    void Player::Update(float dt)
    {
        playerAnim.UpdateAnimation(dt);

        if (IsKeyDown(KEY_LEFT))
        {
            playerAnim.SetAnimationActive(true);
            facingLeft = true;
            SetXVel(-speed);
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            playerAnim.SetAnimationActive(true);
            facingLeft = false;
            SetXVel(speed);
        }
        else
        {
            playerAnim.SetAnimationActive(false);
            SetXVel(0);
        }

        if (IsKeyDown(KEY_DOWN))
        {
            SetYVel(-speed);
        }
        else if (IsKeyDown(KEY_UP))
        {
            SetYVel(speed);
        }
        else
        {
            SetYVel(0);
        }

        DoCollision(dt);
    }

    void Player::Render()
    {
        float worldX = GetXPos() * StickDeath::Map::TILE_SIZE;
        float worldY = GetYPos() * StickDeath::Map::TILE_SIZE;

        int drawX = static_cast<int>(std::floor(worldX)) - GetWidthPixels() / 2;
        int drawY = GameEngine::HEIGHT_VOXELS - static_cast<int>(std::floor(worldY)) - GetHeightPixels();

        GameEngine::DrawImage(
            playerAnim.GetCurrentFrame(),
            drawX,
            drawY,
            {.flipHorizontal = facingLeft});
    }
}