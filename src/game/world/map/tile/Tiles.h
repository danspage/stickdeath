#pragma once

#include "Tile.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <map>
#include <format>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace StickDeath
{
    struct TileRange
    {
        int minX, maxX, minY, maxY;
    };

    struct TileAnimationState
    {
        GameEngine::Util::Timer animTimer;
        int currentFrame;
    };

    inline std::map<std::string, TileProperties> _defaultTileProperties;

    inline std::map<std::string, TileAnimationState> _animationStates;

    // const TileRange GetTileRange(GameEngine::Physics::AABB bounds);

    const std::vector<Tile *> GetTilesInArea(const GameEngine::Physics::AABB &area);

    void InitTileProperties();

    void UpdateTileAnimations(float dt);
}