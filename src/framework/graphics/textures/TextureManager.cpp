#include "TextureManager.h"
#include "TextureAsset.h"
#include "../../util/Timer.h"

#include <iostream>
#include <cstring>

#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

namespace GameEngine::TextureManager
{
    static std::map<std::string, TextureAsset> textureStorage;
    static std::map<std::string, std::unique_ptr<Util::Timer>> globalTextureAnimationTimers;

    void RegisterStaticTexture(const std::string &refPath, const std::string &imagePath)
    {
        textureStorage.try_emplace(refPath, TextureAsset({imagePath}));
    }

    void RegisterAnimatedTexture(const std::string &refPath, const std::string &jsonPath)
    {
        // implementation here
    }

    const GameImage &GetTexture(const std::string &texture)
    {
        // implementation here
    }

    const std::vector<GameImage> &GetTextureAnimationFrames(const std::string &texture)
    {
        // implementation here
    }
}