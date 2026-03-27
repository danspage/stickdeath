#include "Player.h"
#include "../map/Map.h"

namespace StickDeath
{
    void Player::Update(float dt)
    {
        playerAnim.UpdateAnimation(dt);

        if (IsKeyDown(KEY_LEFT))
        {
            playerAnim.SetAnimationActive(true);
            facingLeft = true;
            SetXPos(GetXPos() - dt * speed);
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            playerAnim.SetAnimationActive(true);
            facingLeft = false;
            SetXPos(GetXPos() + dt * speed);
        }
        else
        {
            playerAnim.SetAnimationActive(false);
        }
    }

    void Player::Render()
    {
        float worldX = GetXPos() * StickDeath::Map::TILE_SIZE;
        float worldY = GetYPos() * StickDeath::Map::TILE_SIZE;

        int drawX = static_cast<int>(std::floor(worldX)) - GetWidth() / 2;
        int drawY = GameEngine::HEIGHT_VOXELS - static_cast<int>(std::floor(worldY)) - GetHeight();

        GameEngine::DrawImage(
            playerAnim.GetCurrentFrame(),
            drawX,
            drawY,
            {.flipHorizontal = facingLeft});
    }
}