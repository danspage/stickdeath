#pragma once
#include <vector>
#include <raylib.h>
#include "Constants.h"
#include "Fonts.h"

class Graphics
{
public:
    void Initialize();
    bool isOnScreen(int voxelX, int voxelY);
    void FillPixel(int x, int y, Color color);
    void FillVoxel(int voxelX, int voxelY, Color color);
    void FillBG(Color color);
    void FillRandom();
    void DrawString(std::string font, Color color, int x, int y, std::string str);
    unsigned char *pixels;

private:
    Fonts fonts;
    Color GetRandomRaylibColor()
    {
        // Generate random values for R, G, B components (0 to 255)
        int r = GetRandomValue(0, 255);
        int g = GetRandomValue(0, 255);
        int b = GetRandomValue(0, 255);
        int a = 255; // Fully opaque

        // Return a new Color struct
        return (Color){(unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a};
    };
};