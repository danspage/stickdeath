#pragma once

#include <vector>
#include <memory>

#include "TextureAsset.h"

namespace GameEngine
{
    class AnimationPlayer
    {
    public:
        AnimationPlayer(std::vector<std::shared_ptr<TextureAsset>> frames, float duration, bool autoplay);

        void SetFrames(std::vector<std::shared_ptr<TextureAsset>> frames);
        void Update(float dt);
        void Play();
        void Pause();
        void Stop();
        GameImage *GetCurrentFrame();
        struct AnimationState
        {
            /// @brief Whether the animation will loop, or play through once pausing on the last frame.
            bool looping = false;

            /// @brief A list of frames that the animation will loop through. If the vector contains only one frame, it will act as a static texture.
            std::vector<std::string> frames;
        };

    private:
        std::vector<AnimationState> states;
        Util::Timer animationTimer;
        size_t currentFrame = 0;
        float elapsed = 0.0f;
        float frameDuration = 0.1f;
        bool playing = false;
    };
}