#include "Graphics.h"
#include "../GameEngine.h"

namespace GameEngine::Graphics
{
    void Initialize()
    {
        int fullWidth = GameEngine::WIDTH_VOXELS * GameEngine::VOXEL_SIZE;
        int fullHeight = GameEngine::HEIGHT_VOXELS * GameEngine::VOXEL_SIZE;
        GameEngine::_pixels = (unsigned char *)calloc(fullWidth * fullHeight * 4, 1);
    }

    bool IsOnScreen(int voxelX, int voxelY)
    {
        return (voxelX >= 0 && voxelX < GameEngine::WIDTH_VOXELS && voxelY >= 0 && voxelY < GameEngine::HEIGHT_VOXELS);
    }

    void FillPixel(int pixelX, int pixelY, Color color)
    {
        int pitch = (GameEngine::WIDTH_VOXELS * GameEngine::VOXEL_SIZE);
        int index = (pixelY * pitch + pixelX) * 4;

        GameEngine::_pixels[index] = color.r;
        GameEngine::_pixels[index + 1] = color.g;
        GameEngine::_pixels[index + 2] = color.b;
        GameEngine::_pixels[index + 3] = color.a;
    }

    void FillVoxel(int voxelX, int voxelY, Color color)
    {
        int startX = voxelX * GameEngine::VOXEL_SIZE;
        int startY = voxelY * GameEngine::VOXEL_SIZE;

        for (int y = 0; y < GameEngine::VOXEL_SIZE; y++)
        {
            for (int x = 0; x < GameEngine::VOXEL_SIZE; x++)
            {
                FillPixel(startX + x, startY + y, color);
            }
        }
    }

    Color GetVoxel(int voxelX, int voxelY)
    {
        int index = (((voxelY * GameEngine::VOXEL_SIZE) * GameEngine::VOXEL_SIZE * GameEngine::WIDTH_VOXELS) + (voxelX * GameEngine::VOXEL_SIZE)) * 4;
        return Color({GameEngine::_pixels[index], GameEngine::_pixels[index + 1], GameEngine::_pixels[index + 2], GameEngine::_pixels[index + 3]});
    }

    void FillBG(Color color)
    {
        for (int x = 0; x < GameEngine::WIDTH_VOXELS * GameEngine::VOXEL_SIZE; x++)
        {
            for (int y = 0; y < GameEngine::HEIGHT_VOXELS * GameEngine::VOXEL_SIZE; y++)
            {
                FillPixel(x, y, color);
            }
        }
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