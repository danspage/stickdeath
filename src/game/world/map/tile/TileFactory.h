#pragma once

#include <memory>
#include <string>

#include "Tile.h"
#include "SpikeTile.h"
#include "SawbladeTile.h"

namespace StickDeath::TileFactory
{
    inline std::unique_ptr<Tile> CreateTile(const std::string &tileName, int x, int y)
    {
        if (tileName == "spike")
        {
            return std::make_unique<SpikeTile>(x, y);
        }
        else if (tileName == "sawblade")
        {
            return std::make_unique<SawbladeTile>(x, y);
        }
        
        return std::make_unique<Tile>(x, y, tileName);
    }
}