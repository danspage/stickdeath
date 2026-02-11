#include "Graphics.h"
#include "Constants.h"
#include <random>
#include "Fonts.h"
#include <array>

void Graphics::Initialize()
{
    initializing = true;

    pixels = (unsigned char *)calloc(widthVoxels * voxelSize * heightVoxels * voxelSize * 4, 1);
    fonts.LoadFonts();

    LoadImage("assets/sprites/gui/large_dialogue.png", "large_dialogue");
    LoadImage("assets/sprites/entity/smiley.png", "smiley");
    LoadImage("assets/sprites/entity/player_left.png", "player_left");
    LoadImage("assets/sprites/entity/player_right.png", "player_right");

    initializing = false;
}

void Graphics::LoadImage(std::string filename, std::string imagename)
{
    if (initializing)
    {
        images[imagename] = std::make_unique<GameImage>(filename);
    }
    else
    {
        std::cerr << "An image can only be loaded while the game is initializing (image: " << imagename << ", filename: " << filename << ")" << std::endl;
    }
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
    for (int x = voxelX * voxelSize; x < voxelX * voxelSize + voxelSize; x++)
    {
        for (int y = voxelY * voxelSize; y < voxelY * voxelSize + voxelSize; y++)
        {
            FillPixel(x, y, color);
        }
    }
}

Color Graphics::GetVoxel(int voxelX, int voxelY)
{
    int index = (((voxelY * voxelSize) * voxelSize * widthVoxels) + (voxelX * voxelSize)) * 4;
    return Color({pixels[index], pixels[index + 1], pixels[index + 2], pixels[index + 3]});
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

void Graphics::DrawString(std::string font, Color color, int x, int y, std::string str, bool centered)
{
    std::vector<FontChar> chars = fonts.getStringChars(font, str);

    int strWidth = 0;
    if (centered)
    {
        for (FontChar c : chars)
        {
            if (strWidth != 0)
                strWidth += 1;
            strWidth += c.width;
        }
    }

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
                    if (isOnScreen(x + x2 + charX, y + y2))
                    {
                        if (centered)
                            FillVoxel(x + x2 + charX - strWidth/2, y + y2, color);
                        else
                            FillVoxel(x + x2 + charX, y + y2, color);
                    }
                }
            }
        }

        charX += _char.width + 1;
    }
}

void Graphics::DrawImage(std::string image, int x, int y, bool centeredX = false, bool centeredY = false)
{
    int xOffset = centeredX ? -images[image].get()->width / 2 : 0;
    int yOffset = centeredY ? -images[image].get()->height / 2 : 0;

    for (int imgX = 0; imgX < images[image].get()->width; imgX++)
    {
        for (int imgY = 0; imgY < images[image].get()->height; imgY++)
        {
            int posXonScreen = x + xOffset + imgX;
            int posYonScreen = y + yOffset + (images[image].get()->height - (imgY + 1));

            if (!isOnScreen(posXonScreen, posYonScreen))
            {
                continue;
            }
            else
            {
                Color bgColor = GetVoxel(posXonScreen, posYonScreen);

                int imgIndex = ((images[image].get()->height - (imgY + 1)) * images[image].get()->width + imgX);

                Color imgColor = images[image].get()->pixels[imgIndex];
                Color newColor;

                if (imgColor.a == 0)
                {
                    continue;
                }

                newColor.r = (imgColor.r * imgColor.a + bgColor.r * (255 - imgColor.a)) / 255;
                newColor.g = (imgColor.g * imgColor.a + bgColor.g * (255 - imgColor.a)) / 255;
                newColor.b = (imgColor.b * imgColor.a + bgColor.b * (255 - imgColor.a)) / 255;
                newColor.a = 255;

                FillVoxel(posXonScreen, posYonScreen, newColor);
            }
        }
    }
}

void Graphics::FillRect(int x, int y, int width, int height, Color color)
{
    for (int x2 = x; x2 < x + width; x2++)
    {
        for (int y2 = y; y2 < y + height; y2++)
        {
            if (isOnScreen(x2, y2))
                FillVoxel(x2, y2, color);
        }
    }
}