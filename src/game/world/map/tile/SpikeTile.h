#pragma once

#include "Tile.h"
#include "../../../../engine/util/Timer.h"
#include "../../entity/Player.h"

namespace StickDeath
{
    class SpikeTile : public Tile
    {
    private:
        bool touchedThisFrame = false;
        Player *playerInContact = nullptr;
        GameEngine::Util::Timer playerTouchTimer = GameEngine::Util::Timer(0.5f, true);

        void HurtPlayer(Player *player, bool isFirstContact);

    public:
        SpikeTile(int x, int y) : Tile(x, y, "spike") {}

        void Update(float dt) override;
        void OnCollision(Entity *entity, bool isInside) override;
    };
}