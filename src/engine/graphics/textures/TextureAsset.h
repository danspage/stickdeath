#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>

#include "../../util/Timer.h"
#include "../GameImage.h"

namespace GameEngine
{
    /**
     * See [GameImage](src/engine/graphics/GameImage.h) for the underlying image wrapper.
     *
     * @brief A single asset used to store a texture in the TextureManager's memory.
     * It will not be directly accessed by the game outside of the TextureManager's
     * internal code, rather it will be used to map texture names to image data
     * within it. In the rest of the game's code, a
     * [GameImage](src/engine/graphics/GameImage.h) will be returned when
     * requesting a texture.
     * 
     * @throws std::runtime_error If the TextureAsset is initialized with an empty list of image paths.
     */
    class TextureAsset
    {
    public:
        /**
         * @param imagePaths A list of image paths for the texture, relative to the `assets/images` folder.
         * In the event of a static texture, it will only contain one path, and in the event of an animated
         * texture, it will contain every image used in the order of appearance.
         */
        TextureAsset(std::vector<std::string> imagePaths);

        const GameImage &GetFrame(size_t index) const { return *images.at(index); }
        const std::vector<std::unique_ptr<GameImage>> &GetAllFrames() const { return images; }
        size_t GetNumFrames() const { return images.size(); }
        bool IsAnimated() const { return isAnimated; }

    private:
        std::vector<std::unique_ptr<GameImage>> images;
        bool isAnimated;
    };
}