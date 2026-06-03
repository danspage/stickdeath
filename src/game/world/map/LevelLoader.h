#pragma once

#include <string>
#include <map>
#include <vector>

namespace StickDeath
{
    struct ParsedLevel
    {
        int version = 0;
        int width = 0, height = 0;
        int spawnX = 0, spawnY = 0;
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