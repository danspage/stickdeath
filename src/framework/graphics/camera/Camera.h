#pragma once

#include "../../../framework/basic_types/Positional.h"

#include <functional>

namespace StickDeath
{
    class Camera
    {
    public:
        static float x;
        static float y;

        static void SetPosition(float worldX, float worldY);
        static void MoveBy(float dx, float dy);

        static PointI WorldToScreen(PointF worldPos);
        static PointF ScreenToWorld(PointI screenPos);
        
        static BoundsF GetViewBounds();
    };
}