#include "GameImage.h"

#include <raylib.h>
#include <string>

GameImage::GameImage(std::string filename)
{
    Image tempImg = LoadImage(filename.c_str());
    width = tempImg.width;
    height = tempImg.height;

    pixels = new unsigned char[width * height * 4];

    Color *imgColors = LoadImageColors(tempImg);

    for (int i = 0; i < width * height; i++)
    {
        pixels[i * 4] = imgColors[i].r;
        pixels[i * 4 + 1] = imgColors[i].g;
        pixels[i * 4 + 2] = imgColors[i].b;
        pixels[i * 4 + 3] = imgColors[i].a;
    }
    
    UnloadImageColors(imgColors);
    UnloadImage(tempImg);
}