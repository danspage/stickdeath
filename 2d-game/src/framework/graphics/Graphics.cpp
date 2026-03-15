#include "Graphics.h"

namespace GameEngine
{
    void InitializeGraphics()
    {
        int fullWidth = GameEngine::WIDTH_VOXELS * GameEngine::VOXEL_SIZE;
        int fullHeight = GameEngine::HEIGHT_VOXELS * GameEngine::VOXEL_SIZE;
        GameEngine::_pixels = (uint32_t *)calloc(fullWidth * fullHeight, sizeof(uint32_t));
    }

    bool IsOnScreen(int voxelX, int voxelY)
    {
        return (voxelX >= 0 && voxelX < GameEngine::WIDTH_VOXELS && voxelY >= 0 && voxelY < GameEngine::HEIGHT_VOXELS);
    }

    void FillPixel(int pixelX, int pixelY, Color color)
    {
        uint32_t merged = color.r | (color.g << 8) | (color.b << 16) | (255 << 24);

        GameEngine::_pixels[pixelY * GameEngine::WIDTH_PIXELS + pixelX] = merged;
    }

    void FillPixel(int pixelX, int pixelY, uint32_t r, uint32_t g, uint32_t b)
    {
        int index = pixelY * GameEngine::WIDTH_PIXELS + pixelX;

        uint32_t merged = r | (g << 8) | (b << 16) | (255 << 24);

        GameEngine::_pixels[index] = merged;
    }

    void FillPixel(int pixelX, int pixelY, uint32_t color)
    {
        GameEngine::_pixels[pixelY * GameEngine::WIDTH_PIXELS + pixelX] = color;
    }

    void FillVoxel(int voxelX, int voxelY, Color color)
    {
        const uint32_t merged = color.r | (color.g << 8) | (color.b << 16) | (255 << 24);

        const int topLeftIndex = (voxelY * VOXEL_SIZE) * WIDTH_PIXELS + (voxelX * VOXEL_SIZE);
        _pixels[topLeftIndex] = merged;
        _pixels[topLeftIndex + 1] = merged;
        _pixels[topLeftIndex + WIDTH_PIXELS] = merged;
        _pixels[topLeftIndex + WIDTH_PIXELS + 1] = merged;
    }

    void FillVoxel(int voxelX, int voxelY, uint32_t r, uint32_t g, uint32_t b, uint32_t a)
    {
        // TODO: Add a way to interpolate background pixels for partial alpha
        uint32_t merged = r | (g << 8) | (b << 16) | (255 << 24);

        const int topLeftIndex = (voxelY * VOXEL_SIZE) * WIDTH_PIXELS + (voxelX * VOXEL_SIZE);
        _pixels[topLeftIndex] = merged;
        _pixels[topLeftIndex + 1] = merged;
        _pixels[topLeftIndex + WIDTH_PIXELS] = merged;
        _pixels[topLeftIndex + WIDTH_PIXELS + 1] = merged;
    }

    Color GetVoxel(int voxelX, int voxelY)
    {
        uint32_t packed = _pixels[((voxelY * VOXEL_SIZE) * WIDTH_PIXELS) + (voxelX * VOXEL_SIZE)];

        uint8_t r = static_cast<uint8_t>(packed & 0xFF);
        uint8_t g = static_cast<uint8_t>((packed >> 8) & 0xFF);
        uint8_t b = static_cast<uint8_t>((packed >> 16) & 0xFF);
        uint8_t a = static_cast<uint8_t>((packed >> 24) & 0xFF);

        return Color({r, g, b, a});
    }

    void FillBG(Color color)
    {
        uint32_t merged = color.r | (color.g << 8) | (color.b << 16) | (255 << 24);

        std::fill(_pixels, _pixels + TOTAL_NUM_PIXELS, merged);
    }

    void FillRect(int x, int y, int width, int height, Color color)
    {
        for (int x2 = x; x2 < x + width; x2++)
        {
            for (int y2 = y; y2 < y + height; y2++)
            {
                if (IsOnScreen(x2, y2))
                    FillVoxel(x2, y2, color);
            }
        }
    }
}