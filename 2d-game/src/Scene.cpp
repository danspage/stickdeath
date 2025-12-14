#include "Scene.h"

void Scene::Render(Graphics graphics) {}

void Scene::Update() {}

void Scene::DoKeyboardInput()
{
    if (IsKeyPressed(KEY_LEFT))
        onLeftArrowPressed();
    if (IsKeyPressed(KEY_RIGHT))
        onRightArrowPressed();
    if (IsKeyPressed(KEY_UP))
        onUpArrowPressed();
    if (IsKeyPressed(KEY_DOWN))
        onDownArrowPressed();
    if (IsKeyPressed(KEY_SPACE))
        onSpacePressed();
    if (IsKeyPressed(KEY_ENTER))
        onEnterPressed();
    whileLeftArrowPressed(IsKeyDown(KEY_LEFT));
    whileRightArrowPressed(IsKeyDown(KEY_RIGHT));
    whileUpArrowPressed(IsKeyDown(KEY_UP));
    whileDownArrowPressed(IsKeyDown(KEY_DOWN));
    whileSpacePressed(IsKeyDown(KEY_SPACE));
    whileEnterPressed(IsKeyDown(KEY_ENTER));
}