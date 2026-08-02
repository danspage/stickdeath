#pragma once

#include "AssetLoader.h"

#include "engine/util/StringUtil.h"
#include "engine/graphics/textures/TextureManager.h"

#include <vector>
#include <algorithm>
#include <ranges>

namespace GameEngine::FileIO
{
    void LoadTextures(const std::vector<AssetFilePath> &assetFilePaths)
    {
        std::vector<std::string> checkedPaths;

        for (AssetFilePath entry : assetFilePaths)
        {
            if (std::ranges::find(checkedPaths, entry.fullPath) != checkedPaths.end())
                continue;

            std::string refPath = entry.cleanedPath;
            size_t pos = refPath.find("images/");

            if (entry.fileExtension == ".json")
            {
                TextureManager::RegisterAnimatedTexture(refPath, entry.fullPath);
                checkedPaths.push_back(entry.fullPath);
                for (const auto &imagePath : TextureManager::GetTextureAsset(refPath).GetImagePaths())
                {
                    checkedPaths.push_back(imagePath);
                }
            }
            else if (entry.fileExtension == ".png")
            {
                TextureManager::RegisterStaticTexture(refPath, entry.fullPath);
                checkedPaths.push_back(entry.fullPath);
            }
        }
    }
}