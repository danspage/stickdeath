#pragma once
#include <vector>
#include <memory>
#include <raylib.h>
#include "Constants.h"
#include "Fonts.h"
#include "GameImage.h"

class Graphics
{
public:
    Graphics() : pixels(nullptr) {}
    Graphics(const Graphics &) = delete;
    Graphics &operator=(const Graphics &) = delete;

    void Initialize();
    void LoadImage(std::string filename, std::string imagename);
    bool isOnScreen(int voxelX, int voxelY);
    void FillPixel(int x, int y, Color color);
    void FillVoxel(int voxelX, int voxelY, Color color);
    Color GetVoxel(int voxelX, int voxelY);
    void FillBG(Color color);
    void FillRandom();
    void DrawString(std::string font, Color color, int x, int y, std::string str);
    void DrawImage(std::string image, int x, int y, bool centeredX, bool centeredY);
    void FillRect(int x, int y, int width, int height, Color color);
    unsigned char *pixels;

private:
    Fonts fonts;
    std::map<std::string, std::unique_ptr<GameImage>> images;
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
    bool initializing = false;

};