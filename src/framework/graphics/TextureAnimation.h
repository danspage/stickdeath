#pragma once

#include <vector>
#include <string>

namespace GameEngine
{
    class TextureAnimation
    {
    public:
        TextureAnimation(float delaySeconds, std::vector<std::string> frames)
        {
            animDelaySecs = delaySeconds;
            animFrames = frames;
        }
        void UpdateAnimation(float dt);
        void SetAnimationActive(bool active) { animActive = active; }
        std::string GetCurrentFrame() { return animFrames[animFrame]; }

    private:
        float animDelaySecs = 0.1;
        float lastAnimUpdate = 0;
        int animFrame = 0;
        bool animActive;
        std::vector<std::string> animFrames;
    };
}