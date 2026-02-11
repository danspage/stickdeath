#pragma once

#include "../../Graphics.h"

class RectBlock
{
public:
    RectBlock(int _x, int _y, int _width, int _height) : x(_x), y(_y), width(_width), height(_height) {}
    void render(Graphics* g);
    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }

private:
    int x, y, width, height;
};