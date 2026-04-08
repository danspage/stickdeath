#include "HealthBar.h"

namespace StickDeath::UI
{
    HealthBar::HealthBar(Color _barColor, int defaultValue, int _maxValue, int _xScreenPos, int _yScreenPos, int _width, int _height)
    {
        barColor = _barColor;
        value = defaultValue;
        maxValue = _maxValue;
        xScreenPos = _xScreenPos;
        yScreenPos = _yScreenPos;
        width = _width;
        height = _height;

        barWidth = GetBarWidth();
    }

    int HealthBar::GetBarWidth()
    {
        int maxBarWidth = width - 2;
        float barPercent = (float)value / (float)maxValue;

        return static_cast<int>(std::round((float)maxBarWidth * barPercent));
    }

    void HealthBar::SetValue(int newVal)
    {
        value = newVal;
        barWidth = GetBarWidth();
    }

    void HealthBar::Render()
    {
        GameEngine::FillRect(xScreenPos, yScreenPos, width, height, LIGHTGRAY);
        GameEngine::FillRect(xScreenPos + 1, yScreenPos + 1, barWidth, height - 2, barColor);
    }
}