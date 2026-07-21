#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>

#include "Images.h"
#include "../util/Timer.h"

namespace GameEngine
{
    namespace TextureManager
    {
        /**
         * See [GameImage](src/framework/graphics/GameImage.h) for the underlying image wrapper.
         *
         * @brief A single asset used to store a texture in the TextureManager's memory.
         * It will not be directly accessed by the game outside of the TextureManager's
         * internal code, rather it will be used to map texture names to image data
         * within it. In the rest of the game's code, a
         * [GameImage](src/framework/graphics/GameImage.h) will be returned when
         * requesting a texture.
         */
        class TextureAsset
        {
        public:
            TextureAsset(std::vector<std::string> imagePaths);

            std::vector<GameImage> *GetTextureImages() { return &images; }
        
        private:
            std::vector<GameImage> images;
            bool isAnimated;

        protected:
            std::vector<std::string> imagePaths;
        };

        struct AnimationState
        {
            /// @brief Whether the animation will loop, or play through once pausing on the last frame.
            bool looping = false;

            /// @brief A list of frames that the animation will loop through. If the vector contains only one frame, it will act as a static texture.
            std::vector<std::string> frames;
        };
    }

    class AnimationPlayer
    {
    public:
        AnimationPlayer(std::vector<std::shared_ptr<TextureManager::TextureAsset>> frames, float duration, bool autoplay);

        void SetFrames(std::vector<std::shared_ptr<TextureManager::TextureAsset>> frames);
        void Update(float dt);
        void Play();
        void Pause();
        void Stop();
        GameImage *GetCurrentFrame();

    private:
        std::vector<TextureManager::AnimationState> states;
        Util::Timer animationTimer;
        size_t currentFrame = 0;
        float elapsed = 0.0f;
        float frameDuration = 0.1f;
        bool playing = false;
    };
}