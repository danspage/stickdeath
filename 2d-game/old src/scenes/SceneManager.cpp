#include "SceneManager.h"
#include "../Constants.h"

void SceneManager::markAsInitialized()
{
    if (initialized)
    {
        std::cerr << "The scene manager is already initialized and cannot be initialized again!" << std::endl;
        return;
    }
    initialized = true;
}

void SceneManager::registerScene(std::string _sceneName, std::unique_ptr<Scene> _scene)
{
    scenes[_sceneName] = std::move(_scene);
}

void SceneManager::setScene(std::string scene)
{
    if (!initialized)
    {
        std::cerr << "The scene manager must have scenes registered before the scene can be set!" << std::endl;
        return;
    }

    if (scenes.find(scene) == scenes.end())
    {
        std::cerr << "Tried to load a scene with the name \"" << scene << "\" which does not exist!" << std::endl;
        return;
    }

    if (currentScene != NULL_SCENE)
        scenes[currentScene].get()->onExit();

    currentScene = scene;
    scenes[currentScene].get()->onEnter();
}

void SceneManager::render(Graphics *g)
{
    if (!initialized)
    {
        std::cerr << "The scene manager have scenes registered before it can render!" << std::endl;
        return;
    }
    scenes[currentScene].get()->Render(g, this);
}

void SceneManager::update()
{
    if (!initialized)
    {
        std::cerr << "The scene manager have scenes registered before the scene can update!" << std::endl;
        return;
    }
    scenes[currentScene]->DoKeyboardInput();
    scenes[currentScene]->Update(this);
}

std::string SceneManager::getCurrentSceneName()
{
    return currentScene;
}