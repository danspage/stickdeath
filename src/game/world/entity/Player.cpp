#include "Player.h"
#include "../../../engine/GameEngine.h"
#include "../../../engine/graphics/camera/Camera.h"

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
            // playerAnim.SetAnimationActive(true);
            facingLeft = true;
            GetCollider()->SetXVel(-speed);
        }
        else if (key == SDL_SCANCODE_RIGHT)
        {
            // playerAnim.SetAnimationActive(true);
            facingLeft = false;
            GetCollider()->SetXVel(speed);
        }
    }

    void Player::OnKeyReleased(SDL_Scancode key)
    {
        if (key == SDL_SCANCODE_LEFT || key == SDL_SCANCODE_RIGHT)
        {
            // playerAnim.SetAnimationActive(false);
            GetCollider()->SetXVel(0);
        }
    }

    void Player::Update(float dt)
    {
        // playerAnim.UpdateAnimation(dt);

        const auto hits = GetCollider()->MoveAndDoCollision(dt);

        for (const auto &hit : hits)
        {
            if (hit.tile != nullptr)
            {
                hit.tile->OnCollision(this, hit.isInside);
            }
        }
    }

    void Player::Render()
    {
        float worldX = GetCollider()->GetXPos() * StickDeath::Map::TILE_SIZE_VOXELS;
        float worldY = GetCollider()->GetYPos() * StickDeath::Map::TILE_SIZE_VOXELS;

        const GameEngine::PointF worldTopLeft = {
            worldX - WIDTH_VOXELS/2.0f,
            worldY + HEIGHT_VOXELS,
        };

        const GameEngine::PointI screen = StickDeath::Camera::WorldToScreen(worldTopLeft);

        GameEngine::DrawImage(
            // playerAnim.GetCurrentFrame(),
            "sprites/entity/player/walking_1",
            screen.x,
            screen.y,
            {.flipHorizontal = facingLeft});
    }
}