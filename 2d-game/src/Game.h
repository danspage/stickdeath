#pragma once
#include <vector>
#include <raylib.h>
#include "Graphics.h"

class Game
{
public:
    Game()
        : graphics()
    {
        texture = { 0 };
    }
    void Render();
    Graphics graphics;
    Texture2D texture;
private:
};