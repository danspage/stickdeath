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
        const int startX = voxelX * GameEngine::VOXEL_SIZE;
        const int startY = voxelY * GameEngine::VOXEL_SIZE;
        const uint32_t merged = color.r | (color.g << 8) | (color.b << 16) | (255 << 24);

        for (int y = 0; y < GameEngine::VOXEL_SIZE; y++)
        {
            for (int x = 0; x < GameEngine::VOXEL_SIZE; x++)
            {
                FillPixel(startX + x, startY + y, merged);
            }
        }
    }

    void FillVoxel(int voxelX, int voxelY, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        // TODO: Add a way to interpolate background pixels for partial alpha

        int startX = voxelX * GameEngine::VOXEL_SIZE;
        int startY = voxelY * GameEngine::VOXEL_SIZE;

        for (int y = 0; y < GameEngine::VOXEL_SIZE; y++)
        {
            for (int x = 0; x < GameEngine::VOXEL_SIZE; x++)
            {
                FillPixel(startX + x, startY + y, r, g, b);
            }
        }
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