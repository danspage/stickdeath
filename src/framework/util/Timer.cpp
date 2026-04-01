#include "Timer.h"

namespace GameEngine::Util
{
    Timer::Timer(float intervalSeconds, bool looping)
        : intervalSeconds(std::max(0.001f, intervalSeconds)),
          looping(looping)
    {
    }

    void Timer::Start()
    {
        running = true;
    }

    void Timer::Stop()
    {
        running = false;
    }

    void Timer::Restart()
    {
        elapsedSeconds = 0;
        running = true;
    }

    void Timer::SetInterval(float seconds)
    {
        intervalSeconds = std::max(0.001f, seconds);
    }

    int Timer::UpdateAndGetTicks(float dt)
    {
        if (!running)
            return 0;

        int numTicks = 0;

        elapsedSeconds += dt;

        while (elapsedSeconds >= intervalSeconds)
        {
            numTicks++;

            if (looping)
            {
                elapsedSeconds -= intervalSeconds;
            }
            else
            {
                running = false;
                elapsedSeconds = 0;
                break;
            }
        }

        return numTicks;
    }
}