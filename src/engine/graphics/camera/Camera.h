#pragma once

#include "../../../engine/basic_types/Positional.h"

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

        static GameEngine::PointI WorldToScreen(GameEngine::PointF worldPos);
        static GameEngine::PointF ScreenToWorld(GameEngine::PointI screenPos);
        
        static GameEngine::BoundsF GetWorldBounds();
    };
}