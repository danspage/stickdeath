#pragma once

#include "Tile.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <format>
#include <stdexcept>

#include <nlohmann/json.hpp>
#include <typeindex>

using json = nlohmann::json;

namespace StickDeath
{
    struct TileDefinition
    {
        std::string texturePath;
        TileProperties properties;
    };

    inline std::map<std::string, TileDefinition> _defaultTileProperties;

    void InitTileProperties();
}