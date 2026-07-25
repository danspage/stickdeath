#pragma once

#include "Tile.h"
#include "../../../../engine/util/Timer.h"
#include "../../entity/Player.h"

namespace StickDeath
{
    class SawbladeTile : public Tile
    {
    private:
        bool touchedThisFrame = false;
        Player *playerInContact = nullptr;
        GameEngine::Util::Timer playerTouchTimer = GameEngine::Util::Timer(0.1f, true);

        void HurtPlayer(Player *player);

    public:
        SawbladeTile(int x, int y) : Tile(x, y, "sawblade") {}

        void Update(float dt) override;
        void OnCollision(Entity *entity, bool isInside) override;
    };
}