#include "AssetLoader.h"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "engine/util/StringUtil.h"
#include "engine/graphics/Images.h"
#include "engine/graphics/Fonts.h"
#include "engine/graphics/textures/TextureManager.h"

#include "TextureLoader.h"

namespace fs = std::filesystem;

void _LoadAssetFile(const std::string &path, std::string cleanedPath, const std::string &fileExtension)
{
    if (fileExtension == ".png")
    {
        size_t pos = cleanedPath.find("images/");
        if (pos != std::string::npos)
        {
            cleanedPath.erase(pos, std::string("images/").length());
        }

        std::cout << "LOADING IMAGE: " << cleanedPath << std::endl;

        GameEngine::_LoadImage(cleanedPath, path);
    }
    else if (fileExtension == ".2df")
    {
        std::cout << "LOADING FONT: " << cleanedPath << std::endl;

        GameEngine::_LoadFont(path);
    }
}

namespace GameEngine::FileIO
{
    std::vector<AssetFilePath> GetAssetsInFolder(const std::string &folderPath)
    {
        std::vector<std::string> initialFilePaths;
        std::vector<AssetFilePath> finalFilePaths;

        try
        {
            if (fs::exists(folderPath) && fs::is_directory(folderPath))
            {
                // The recursive iterator does all the heavy lifting
                for (const auto &entry : fs::recursive_directory_iterator(folderPath))
                {

                    // We only want files, not the folder names themselves
                    if (fs::is_regular_file(entry))
                    {
                        initialFilePaths.push_back(entry.path().string());
                    }
                }
            }
            else
            {
                throw std::runtime_error("Path does not exist or is not a directory.");
            }
        }
        catch (const fs::filesystem_error &e)
        {
            throw std::runtime_error("Error: " + std::string(e.what()));
        }

        for (const auto &file : initialFilePaths)
        {
            fs::path p(file);
            const std::string &cleanedPath = fs::relative(p, "assets").replace_extension("").string();
            const std::string &fileExtension = p.extension().string();

            // std::cout << "Found: " << cleanedPath << std::endl;

            finalFilePaths.push_back({cleanedPath, file, fileExtension});
        }

        return finalFilePaths;
    }

    void LoadAllAssets()
    {
        LoadTextures(GetAssetsInFolder("assets/images"));
    }
}