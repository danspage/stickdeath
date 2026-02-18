#pragma once

#include <vector>
#include <raylib.h>

namespace GameEngine::Graphics
{
    void Initialize();
    // void LoadImage(std::string filename, std::string imagename);
    bool IsOnScreen(int voxelX, int voxelY);
    void FillPixel(int pixelX, int pixelY, Color color);
    void FillVoxel(int voxelX, int voxelY, Color color);
    Color GetVoxel(int voxelX, int voxelY);
    void FillBG(Color color);
    // void FillRandom();
    // void DrawString(std::string font, Color color, int x, int y, std::string str, bool centered = false);
    // void DrawImage(std::string image, int x, int y, bool centeredX, bool centeredY);
    void FillRect(int x, int y, int width, int height, Color color);
}