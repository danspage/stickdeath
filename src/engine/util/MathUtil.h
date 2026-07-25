#pragma once

#include <cmath>

namespace GameEngine::Util
{

    inline float RandomFloat(float min, float max)
    {
        float random = ((float)rand()) / (float)RAND_MAX;
        float diff = max - min;
        float r = random * diff;
        return min + r;
    }

    enum class AngleUnit
    {
        Radians,
        Degrees
    };

    inline float RadiansToDegrees(float radians)
    {
        return radians * (180/M_PI);
    }

    inline float DegreesToRadians(float degrees)
    {
        return degrees * (M_PI/180);
    }
}