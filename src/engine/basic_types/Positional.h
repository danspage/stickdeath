#pragma once

#include <cmath>

namespace GameEngine
{
    struct PointI
    {
        int x, y;

        PointI &operator+=(const PointI &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }
        PointI operator+(const PointI &other) const
        {
            PointI result = *this;
            result += other;
            return result;
        }
        PointI &operator-=(const PointI &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        PointI operator-(const PointI &other) const
        {
            PointI result = *this;
            result -= other;
            return result;
        }
        PointI operator*(int scalar) const
        {
            return PointI{x * scalar, y * scalar};
        }
    };
    struct PointF
    {
        float x, y;

        PointF &operator+=(const PointF &other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }
        PointF operator+(const PointF &other) const
        {
            PointF result = *this;
            result += other;
            return result;
        }
        PointF &operator-=(const PointF &other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        PointF operator-(const PointF &other) const
        {
            PointF result = *this;
            result -= other;
            return result;
        }
        PointF operator*(float scalar) const
        {
            return PointF{x * scalar, y * scalar};
        }
    };

    struct BoundsI
    {
        int left;
        int right;
        int top;
        int bottom;
    };
    struct BoundsF
    {
        float left;
        float right;
        float top;
        float bottom;
    };
}