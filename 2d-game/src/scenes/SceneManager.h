#pragma once

#include <map>
#include <string>
#include "Scene.h"
#include "../Graphics.h"

class SceneManager
{
public:
    SceneManager() {};
    void registerScene(std::string _sceneName, std::unique_ptr<Scene> _scene);
    void setScene(std::string scene);
    void render(Graphics* g);
    void update();
    void markAsInitialized();
    std::string getCurrentSceneName();
private:
    std::map<std::string, std::unique_ptr<Scene>> scenes;
    std::string currentScene = "NULL_SCENE";
    bool initialized = false;
};