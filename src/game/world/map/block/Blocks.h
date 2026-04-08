#pragma once

#include "Block.h"

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
    struct BlockDefinition
    {
        std::string texturePath;
        BlockProperties properties;
    };

    inline std::map<std::string, BlockDefinition> _defaultBlockProperties;

    void InitBlockProperties();
}