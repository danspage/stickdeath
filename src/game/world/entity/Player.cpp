#include "Player.h"
#include "../../../framework/GameEngine.h"

namespace StickDeath
{
    void Player::OnKeyPressed(SDL_Scancode key)
    {
        if (key == SDL_SCANCODE_UP && GetCollider()->IsOnGround())
        {
            // Jump
            GetCollider()->SetYVel(15);
        }
    }

    void Player::OnKeyHeld(SDL_Scancode key)
    {
        if (key == SDL_SCANCODE_LEFT)
        {
            playerAnim.SetAnimationActive(true);
            facingLeft = true;
            GetCollider()->SetXVel(-speed);
        }
        else if (key == SDL_SCANCODE_RIGHT)
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
    }

    void Player::OnKeyReleased(SDL_Scancode key)
    {
        if (key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT)
        {
            playerAnim.SetAnimationActive(false);
            GetCollider()->SetXVel(0);
        }
    }

    void Player::Update(float dt)
    {
        playerAnim.UpdateAnimation(dt);

        const auto hits = GetCollider()->DoCollision(dt);

        for (const auto &hit : hits)
        {
            if (hit.block != nullptr)
            {
                hit.block->OnCollision(this, hit.isInside);
            }
        }
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