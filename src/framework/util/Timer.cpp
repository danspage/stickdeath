#include "Timer.h"

namespace GameEngine::Util
{
    Timer::Timer(float intervalSeconds, bool looping)
        : intervalSeconds(std::max(0.001f, intervalSeconds)),
          looping(looping)
    {
    }

    /// @brief Starts the timer. If the timer is already running, this does nothing.
    void Timer::Start()
    {
        running = true;
    }

    /// @brief Stops the timer, but does not reset the elapsed time. Calling Start() again will resume from where it left off.
    void Timer::Stop()
    {
        running = false;
    }

    /// @brief Resets the timer to 0 and starts it.
    void Timer::Restart()
    {
        elapsedSeconds = 0;
        running = true;
    }

    /// @brief Sets the interval for the timer. If the timer is running, the new interval will take effect immediately.
    void Timer::SetInterval(float seconds)
    {
        intervalSeconds = std::max(0.001f, seconds);
    }

    /// @brief Updates the timer with the given delta time and returns the number of ticks that have occurred since the last update. If the timer is not running, this returns 0.
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