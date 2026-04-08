#include "SpikeBlock.h"

#include "../../entity/Player.h"

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

        player->RemoveHealth(1);
        std::cout << "Spike hurt player. Health: " << player->GetHealth() << std::endl;
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