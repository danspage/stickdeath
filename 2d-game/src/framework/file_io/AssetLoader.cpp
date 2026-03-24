#include "AssetLoader.h"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "framework/util/StringUtil.h"
#include "framework/graphics/Images.h"
#include "framework/graphics/Fonts.h"

namespace fs = std::filesystem;

void _LoadAssetFile(std::string path, std::string cleanedPath, std::string fileExtension)
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

namespace GameEngine
{
    void LoadAllAssets()
    {
        std::string path = "assets";
        std::vector<std::string> filePaths;

        try
        {
            if (fs::exists(path) && fs::is_directory(path))
            {
                // The recursive iterator does all the heavy lifting
                for (const auto &entry : fs::recursive_directory_iterator(path))
                {

                    // We only want files, not the folder names themselves
                    if (fs::is_regular_file(entry))
                    {
                        filePaths.push_back(entry.path().string());
                    }
                }
            }
            else
            {
                std::cerr << "Path does not exist or is not a directory." << std::endl;
            }
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Print the results to verify
        for (const auto &file : filePaths)
        {
            fs::path p(file);
            std::string cleanedPath = fs::relative(p, "assets").replace_extension("").string();

            // std::cout << "Found: " << cleanedPath << std::endl;

            _LoadAssetFile(file, cleanedPath, p.extension().string());

            //     if (GameUtil::ends_with(file, ".png"))
            // {

            //     GameEngine::LoadImage(cleanedPath, new GameImage(file.c_str()));

            // }
        }
    }
}