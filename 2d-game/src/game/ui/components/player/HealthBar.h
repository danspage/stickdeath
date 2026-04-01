#pragma once

#include <raylib.h>

#include "../../../../framework/graphics/Graphics.h"

namespace StickDeath::UI
{
    class HealthBar
    {
    public:
        HealthBar(Color _barColor, int defaultValue, int _maxValue, int _xScreenPos, int _yScreenPos, int _width, int _height);

        void SetValue(int newVal);
        void Render();
    private:
        Color barColor;
        
        int xScreenPos;
        int yScreenPos;
        int width;
        int height;

        int value;
        int maxValue;
        int barWidth;

        int GetBarWidth();
    };
}