#pragma once

#include <string>
#include <map>
#include <vector>

namespace StickDeath
{
    struct ParsedLevel
    {
        int version = -1;
        int width = -1, height = -1;
        int spawnX = -1, spawnY = -1;
        std::map<char, std::string> legend;
        std::vector<std::string> rows;
    };

    class LevelLoader
    {
    public:
        static ParsedLevel ParseLevel(const std::string &levelName);
        static void ApplyLevel(const ParsedLevel &level);
    };
}