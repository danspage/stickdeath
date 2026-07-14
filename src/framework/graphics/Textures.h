#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "Images.h"
#include "../util/Timer.h"

namespace GameEngine
{
    class Texture
    {
    public:
        Texture(std::string name, GameImage &image);

        virtual ~Texture() = default;

        GameImage &GetCurrentImage() { return image; }

    protected:
        std::string name;
        GameImage &image;
    };

    class LoopingTexture : public Texture
    {
    public:
        LoopingTexture(const std::string name, std::vector<GameImage *> frames, float interval)
            : Texture(std::move(name), *frames.front()), frames(std::move(frames)), interval(interval) {} // Move the constructor to the .cpp

        GameImage &GetCurrentImage(); // Add override keyword in the .cpp

    private:
        std::vector<GameImage *> frames;
        float interval;
    };

    class AnimatedTexture : public Texture
    {
    public:
        AnimatedTexture(std::string name, GameImage *defaultFrame, std::map<std::string, std::vector<GameImage *>> frames, float interval)
            : Texture(name, *defaultFrame),
              animationStates(std::move(animationStates)),
              frameTimer(Util::Timer(interval, true))
        {
        } // Move the constructor to the .cpp file

        void SetAnimationState(std::string state) { currentState = std::move(state); }
        void PlayAnimation();
        void PauseAnimation() { frameTimer.Stop(); }
        void StopAnimation();

        const GameImage &GetCurrentImage(); // Add override keyword in the .cpp

    private:
        std::map<std::string, std::vector<GameImage *>> animationStates;
        Util::Timer frameTimer;
        float elapsed = 0.0f;
        int currentFrame = 0; // Set to -1 when playing is false
        bool playing = false;
        std::string currentState;
    };

    namespace TextureManager
    {
        inline std::map<std::string, std::unique_ptr<Texture>> textures;

        inline std::map<std::string, Util::Timer> loopingTextureTimers;

        void RegisterTexture(std::unique_ptr<Texture> texture);
    }
}