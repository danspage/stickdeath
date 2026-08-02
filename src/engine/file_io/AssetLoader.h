#pragma once

#include <string>
#include <vector>

namespace GameEngine::FileIO
{
    struct AssetFilePath
    {
        std::string cleanedPath;
        std::string fullPath;
        std::string fileExtension;
    };

    void LoadAllAssets();
}