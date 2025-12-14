#include "Graphics.h"
#include "Constants.h"
#include <random>
#include "Fonts.h"
#include <array>

void Graphics::Initialize()
{
    pixels = (unsigned char *)calloc(widthVoxels * voxelSize * heightVoxels * voxelSize * 4, 1);
    fonts.LoadFonts();
}

bool Graphics::isOnScreen(int voxelX, int voxelY)
{
    return (voxelX >= 0 && voxelY >= 0 && voxelX < widthVoxels && voxelY < heightVoxels);
}

void Graphics::FillPixel(int x, int y, Color color)
{
    int index = ((y * voxelSize * widthVoxels) + x) * 4;
    pixels[index] = color.r;
    pixels[index + 1] = color.g;
    pixels[index + 2] = color.b;
    pixels[index + 3] = 255;
}

void Graphics::FillVoxel(int voxelX, int voxelY, Color color)
{
    if (isOnScreen(voxelX, voxelY))
    {
        for (int x = voxelX * voxelSize; x < voxelX * voxelSize + voxelSize; x++)
        {
            for (int y = voxelY * voxelSize; y < voxelY * voxelSize + voxelSize; y++)
            {
                FillPixel(x, y, color);
            }
        }
    }
}

void Graphics::FillBG(Color color)
{
    for (int x = 0; x < widthVoxels * voxelSize; x++)
    {
        for (int y = 0; y < heightVoxels * voxelSize; y++)
        {
            FillPixel(x, y, color);
        }
    }
}

void Graphics::FillRandom()
{

    for (int x = 0; x < widthVoxels; x++)
    {
        for (int y = 0; y < heightVoxels; y++)
        {
            FillVoxel(x, y, GetRandomRaylibColor());
        }
    }
}

void Graphics::DrawString(std::string font, Color color, int x, int y, std::string str)
{
    std::vector<FontChar> chars = fonts.getStringChars(font, str);

    int charX = 0;

    for (FontChar _char : chars)
    {
        for (int x2 = 0; x2 < _char.width; x2++)
        {
            for (int y2 = 0; y2 < _char.height; y2++)
            {
                int charDataIndex = (y2 * _char.width) + x2;
                if (_char.pixels[charDataIndex] == 1)
                {
                    FillVoxel(x + x2 + charX, y + y2, color);
                }
            }
        }

        charX += _char.width + 1;
    }
}