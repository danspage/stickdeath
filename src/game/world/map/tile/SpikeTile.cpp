#include "SpikeTile.h"

#include <algorithm>
#include <cmath>

namespace StickDeath
{
    void SpikeTile::HurtPlayer(Player *player, bool isFirstContact)
    {
        if (player == nullptr)
            return;

        const int additionalDamage =
            isFirstContact ? std::max(0, static_cast<int>(std::round(player->GetYVel() / -5.0f))) : 0;
        player->RemoveHealth(1 + additionalDamage);
    }

    void SpikeTile::Update(float dt)
    {
        if (playerInContact != nullptr)
        {
            const int ticks = playerTouchTimer.UpdateAndGetTicks(dt);
            for (int i = 0; i < ticks; i++)
            {
                HurtPlayer(playerInContact, false);
            }

            if (!touchedThisFrame)
            {
                playerInContact = nullptr;
                playerTouchTimer.Stop();
            }
        }

        touchedThisFrame = false;
    }

    void SpikeTile::OnCollision(Entity *entity, bool isInside)
    {
        if (!isInside)
            return;

        Player *player = dynamic_cast<Player *>(entity);
        if (player == nullptr)
            return;

        // First contact with this player: immediate hit + start repeat timer.
        if (playerInContact != player)
        {
            playerInContact = player;
            HurtPlayer(player, true);
            playerTouchTimer.Restart();
        }

        touchedThisFrame = true;
    }
}