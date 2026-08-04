#include "TextureManager.h"
#include "TextureAsset.h"
#include "../../util/Timer.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <map>

#include <SDL2/SDL_image.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace GameEngine::TextureManager
{
    namespace
    {
        /// @brief A class to manage the state of a globally looping animation.
        class GlobalAnimation
        {
        public:
            GlobalAnimation(const TextureAsset *asset, float interval)
                : asset(asset), timer(interval, true) {}

            const GameImage &GetCurrentFrame() const { return asset->GetFrame(currentFrame); }

            void Update(float dt)
            {
                int ticks = timer.UpdateAndGetTicks(dt);
                if (ticks > 0)
                    currentFrame = (currentFrame + ticks) % asset->GetNumFrames();
            }

        private:
            const TextureAsset *asset;
            Util::Timer timer;
            int currentFrame = 0;
        };
    }

    static std::map<std::string, TextureAsset> textureStorage;
    static std::map<std::string, GlobalAnimation> globalAnimations;

    void RegisterStaticTexture(const std::string &refPath, const std::string &imagePath)
    {
        std::cout << "LOADING A STATIC TEXTURE! " << refPath << std::endl;
        textureStorage.try_emplace(refPath, TextureAsset({imagePath}));
    }

    void RegisterAnimatedTexture(const std::string &refPath, const std::string &jsonPath)
    {
        std::cout << "LOADING AN ANIMATED TEXTURE! " << refPath << std::endl;

        std::ifstream propsFile(jsonPath);
        if (!propsFile.is_open())
        {
            throw std::runtime_error("Could not open " + jsonPath);
            return;
        }

        json animJson = json::parse(propsFile);

        if (!animJson.contains("textures"))
            throw std::runtime_error("The animation config file at " + jsonPath + " does not contain a textures list.");

        if (!animJson.contains("interval_seconds"))
            throw std::runtime_error("The animation config file at " + jsonPath + " does not contain an interval time.");

        if (!animJson.contains("global_loop"))
            throw std::runtime_error("The animation config file at " + jsonPath + " does not contain a bool for globally looping.");

        // Load textures
        const json &texturesList = animJson.at("textures");
        if (!texturesList.is_array())
            throw std::runtime_error("The textures entry inside of " + jsonPath + " must be an array.");

        std::vector<std::string> images;
        images.reserve(texturesList.size());

        for (const auto &entry : texturesList)
        {
            if (!entry.is_string())
                throw std::runtime_error("The animation textures inside " + jsonPath + " must be strings.");
            images.emplace_back("assets/textures/" + entry.get<std::string>() + ".png");
        }

        // Read timing/mode
        float interval = animJson.at("interval_seconds").get<float>();
        float globalLoop = animJson.at("global_loop").get<bool>();

        // Register image asset to texture storage using the paths in the json.
        textureStorage.try_emplace(refPath, TextureAsset(images));

        // If the animation is set to globally loop, register it to the global animation map.
        if (globalLoop)
        {
            globalAnimations.try_emplace(refPath, GlobalAnimation(&textureStorage.at(refPath), interval));
        }
    }

    /**
     * @brief Get the Texture object
     *
     * @param texture
     * @return const GameImage&
     *
     *
     * TODO: This will need to detect if an animation is in the global loop, since
     * since it will exist in the texture storage anyway for use with AnimationPlayers.
     * If it is in the global loop, it will return the current frame of the animation
     * synced to the game's clock. If it is not in the global loop, it will simply return
     * the first frame of the texture asset, since it is not meant to be used as a global
     * animation.
     */
    const GameImage &GetTexture(const std::string &texture)
    {
        auto it = globalAnimations.find(texture);
        if (it != globalAnimations.end())
            return it->second.GetCurrentFrame();

        return textureStorage.at(texture).GetFrame(0);
    }

    const TextureAsset &GetTextureAsset(const std::string &texture)
    {
        return textureStorage.at(texture);
    }

    void UpdateGlobalAnimations(float dt)
    {
        for (auto &entry : globalAnimations)
        {
            entry.second.Update(dt);
        }
    }
}