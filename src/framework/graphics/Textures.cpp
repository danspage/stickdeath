#include "Textures.h"

namespace GameEngine
{
    namespace TextureManager
    {
        TextureAsset::TextureAsset(std::vector<std::string> imagePaths)
        : imagePaths(imagePaths)
        {
            if (imagePaths.size() == 0)
            {
                throw std::runtime_error("A TextureAsset must contain one or more image paths, but was initialized with none!");
            }

            isAnimated = imagePaths.size() > 1;

            for (std::string path : imagePaths)
            {
                images.emplace_back(GameEngine::GetImage(path));
            }
        }
    }
}