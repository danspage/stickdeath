#include "GameImage.h"
#include <raylib.h>

GameImage::GameImage(std::string filename)
{
    Image tempImg = LoadImage(filename.c_str());
    width = tempImg.width;
    height = tempImg.height;
    pixels = LoadImageColors(tempImg);
}