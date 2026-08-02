#include "TextureAsset.h"

#include "../GameImage.h"

namespace GameEngine
{
    TextureAsset::TextureAsset(std::vector<std::string> imagePaths)
        : imagePaths(std::move(imagePaths))
    {
        if (this->imagePaths.empty())
            throw std::runtime_error("A TextureAsset must contain one or more image paths, but was initialized with none!");

        isAnimated = this->imagePaths.size() > 1;

        for (std::string &path : this->imagePaths)
        {
            images.emplace_back(std::make_unique<GameImage>(path));
        }
    }

}