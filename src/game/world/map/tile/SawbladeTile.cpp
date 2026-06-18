#include "SawbladeTile.h"

namespace StickDeath
{
    void SawbladeTile::HurtPlayer(Player *player)
    {
        player->RemoveHealth(1);
    }

    void SawbladeTile::Update(float dt)
    {
        if (playerInContact != nullptr)
        {
            const int ticks = playerTouchTimer.UpdateAndGetTicks(dt);
            for (int i = 0; i < ticks; i++)
            {
                HurtPlayer(playerInContact);
            }

            if (!touchedThisFrame)
            {
                playerInContact = nullptr;
                playerTouchTimer.Stop();
            }
        }

        touchedThisFrame = false;
    }

    void SawbladeTile::OnCollision(Entity *entity, bool isInside)
{
    if (!isInside)
        return;

    Player *player = dynamic_cast<Player *>(entity);
    if (player == nullptr)
        return;

    // Track whichever player is currently colliding.
    if (playerInContact != player)
    {
        playerInContact = player;
        HurtPlayer(player);
        playerTouchTimer.Restart();
    }

    touchedThisFrame = true;
}
}