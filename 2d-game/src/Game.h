#pragma once
#include <vector>
#include <raylib.h>
#include <map>
#include <string>
#include <memory>
#include "Graphics.h"
#include "Scene.h"
#include "BouncingBallScene.h"

class Game
{
public:
    Game()
        : graphics()
    {
        texture = { 0 };
        scenes["bouncing_ball"] = std::make_unique<BouncingBallScene>();
    }
    void Render();
    Graphics graphics;
    Texture2D texture;
private:
    std::map<std::string, std::unique_ptr<Scene>> scenes;
    std::string currentScene = "bouncing_ball";
};