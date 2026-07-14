#pragma once

#include <map>
#include <memory>
#include <string>

#include "Textures.h"
#include "../util/Timer.h"

namespace GameEngine::TextureManager
{
    inline std::map<std::string, std::unique_ptr<TextureAsset>> textures;

    void RegisterTexture(std::unique_ptr<TextureAsset> texture);
}