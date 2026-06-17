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
    struct TileAnimationState
    {
        GameEngine::Util::Timer animTimer;
        int currentFrame;
    };

    inline std::map<std::string, TileProperties> _defaultTileProperties;

    inline std::map<std::string, TileAnimationState> _animationStates;

    void InitTileProperties();

    void UpdateTileAnimations(float dt);
}