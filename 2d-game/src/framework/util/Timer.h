#pragma once

#include <algorithm>

namespace GameEngine::Util
{
    class Timer
    {
    private:
        float intervalSeconds;
        float elapsedSeconds = 0;
        bool running = false;
        bool looping;
    
    public:
        Timer(float _intervalSeconds, bool _looping);

        void Start();
        void Stop();
        void Restart();
        void SetInterval(float seconds);
        int UpdateAndGetTicks(float dt);

        bool IsRunning() const { return running; }
    };
}