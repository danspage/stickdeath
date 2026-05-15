#include "SpikeBlock.h"

#include <cmath>

#include "../../entity/Player.h"
#include "../../../../framework/GameEngine.h"
#include "../../../states/TestState.h"

namespace StickDeath
{
    SpikeBlock::SpikeBlock(int x, int y) : Block(x, y, "spike")
    {
    }

    void SpikeBlock::HurtPlayer()
    {
        if (targetedEntityForCollision == nullptr)
            return;

        Player *player = dynamic_cast<Player *>(targetedEntityForCollision);
        if (player == nullptr)
            return; // Not a Player

        int additionalDamage = std::max(0, static_cast<int>(std::round(player->GetYVel() / -5.0f)));

        player->RemoveHealth(1 + additionalDamage);
    }

    void SpikeBlock::Update(float dt)
    {
        if (touchingPlayer)
        {
            const int ticks = playerTouchTimer.UpdateAndGetTicks(dt);
            for (int i = 0; i < ticks; i++)
            {
                HurtPlayer();
            }
        }

        touchingPlayer = touchedThisFrame;
        touchedThisFrame = false;

        if (!touchingPlayer)
        {
            playerTouchTimer.Stop();
        }
    }

    void SpikeBlock::OnCollision(Entity *entity, bool isInside)
    {
        if (!isInside)
        {
            targetedEntityForCollision = entity;
            return;
        }

        if (!touchedThisFrame && !touchingPlayer)
        {
            HurtPlayer();
            playerTouchTimer.Restart();
        }

        touchedThisFrame = true;
    }
}