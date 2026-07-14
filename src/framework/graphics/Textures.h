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
    class TextureAsset
    {
    public:
        TextureAsset(std::string name, std::string image);

        GameImage *GetTextureImage() { return GetImage(image); }

    protected:
        std::string name;
        std::string image;
    };

    // class LoopingTextureAsset : public TextureAsset
    // {
    // public:
    //     LoopingTextureAsset(std::string name, std::vector<std::string> frames, float interval)
    //         : TextureAsset(name, frames.front()), frames(frames), interval(interval) {} // Move the constructor to the .cpp

    //     GameImage *GetCurrentImage() override;

    // private:
    //     Util::Timer animationTimer;
    //     std::vector<std::string> frames;
    //     float interval;
    // };

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

    private:
        std::vector<std::shared_ptr<GameImage>> frames;
        Util::Timer animationTimer;
        size_t currentFrame = 0;
        float elapsed = 0.0f;
        float frameDuration = 0.1f;
        bool playing = false;
    };

    // class AnimatedTexture : public TextureAsset
    // {
    // public:
    //     AnimatedTexture(std::string name, std::string defaultFrame, std::map<std::string, std::vector<std::string>> animationStates, float interval)
    //         : TextureAsset(name, defaultFrame),
    //           animationStates(animationStates),
    //           frameTimer(Util::Timer(interval, true))
    //     {
    //     } // Move the constructor to the .cpp file

    //     void SetAnimationState(std::string state) { currentState = std::move(state); }
    //     void PlayAnimation();
    //     void PauseAnimation() { frameTimer.Stop(); }
    //     void StopAnimation();

    //     GameImage *GetCurrentImage() override;

    // private:
    //     std::map<std::string, std::vector<std::string>> animationStates;
    //     Util::Timer frameTimer;
    //     float elapsed = 0.0f;
    //     int currentFrame = 0; // Set to -1 when playing is false
    //     bool playing = false;
    //     std::string currentState;
    // };
}