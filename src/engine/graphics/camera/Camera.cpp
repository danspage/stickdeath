#include "Camera.h"

#include "../../GameEngine.h"

#include <cmath>

namespace StickDeath
{
    float Camera::x = 0.0f;
    float Camera::y = 0.0f;

    void Camera::SetPosition(float worldX, float worldY)
    {
        x = worldX;
        y = worldY;
    }

    void Camera::MoveBy(float dx, float dy)
    {
        x += dx;
        y += dy;
    }

    GameEngine::PointI Camera::WorldToScreen(GameEngine::PointF worldPos)
    {
        const int screenX = static_cast<int>(std::lround(worldPos.x - x));
        const int screenY = static_cast<int>(std::lround(GameEngine::HEIGHT_VOXELS - (worldPos.y - y)));
        return {screenX, screenY};
    }

    GameEngine::PointF Camera::ScreenToWorld(GameEngine::PointI screenPos)
    {
        const float worldX = x + static_cast<float>(screenPos.x);
        const float worldY = y + (GameEngine::HEIGHT_VOXELS - static_cast<float>(screenPos.y));
        return {worldX, worldY};
    }

    GameEngine::BoundsF Camera::GetWorldBounds()
    {
        return {
            x,
            x + static_cast<float>(GameEngine::WIDTH_VOXELS),
            y + static_cast<float>(GameEngine::HEIGHT_VOXELS),
            y
        };
    }
}