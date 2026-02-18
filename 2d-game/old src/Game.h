#pragma once
#include <vector>
#include <raylib.h>
#include <map>
#include <string>
#include <memory>
#include "Graphics.h"
#include "scenes/Scene.h"
#include "scenes/SceneManager.h"

class Game
{
public:
    Game()
    {
        texture = { 0 };
    }
    void Render();
    void init();
    Graphics* graphics;
    Texture2D texture;
    SceneManager* sm;
private:
};