#pragma once
#include <string>
#include <raylib.h>

class GameImage
{
public:
    GameImage(std::string filename);
    int width;
    int height;
    Color *pixels;
};