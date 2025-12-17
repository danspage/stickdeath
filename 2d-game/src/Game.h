#pragma once
#include <vector>
#include <raylib.h>
#include <map>
#include <string>
#include <memory>
#include "Graphics.h"
#include "scenes/Scene.h"
#include "scenes/BouncingBallScene.h"

class Game
{
public:
    Game()
    {
        texture = { 0 };
        scenes["bouncing_ball"] = std::make_unique<BouncingBallScene>();
    }
    void Render();
    Graphics* graphics;
    Texture2D texture;
private:
    std::map<std::string, std::unique_ptr<Scene>> scenes;
    std::string currentScene = "bouncing_ball";
};