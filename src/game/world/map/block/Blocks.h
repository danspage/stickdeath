#pragma once

#include "Block.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <map>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace StickDeath
{
    struct BlockProperty { std::string key; std::string value; };
    
    inline std::map<std::string, std::map<std::string, std::string>> _defaultBlockProperties;

    void InitBlockProperties();
}