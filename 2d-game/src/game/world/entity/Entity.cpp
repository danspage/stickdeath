#include "Entity.h"

namespace StickDeath
{
    int Entity::GetTileToLeftOfEntity()
    {
        return std::floor(GetXPos() - (GetWidth() / 2));
    }

    int Entity::GetTileToRightOfEntity()
    {
        return std::floor(GetXPos() + (GetWidth() / 2));
    }

    int Entity::GetTileAboveEntity()
    {
        return std::floor(GetYPos() + GetHeight());
    }

    int Entity::GetTileBelowEntity()
    {
        return std::floor(GetYPos());
    }
}