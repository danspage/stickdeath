#include "Scene.h"
#include <raylib.h>
#include <iostream>
#include "SceneManager.h"
#include <chrono>
#include <iomanip>


double _lastKBUpdate = std::chrono::system_clock::now().time_since_epoch().count();
void Scene::DoKeyboardInput()
{
    auto _now = std::chrono::system_clock::now();
    std::chrono::duration<double> seconds = _now.time_since_epoch();
    double time_since_epoch = seconds.count();

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

    whileLeftArrowPressed(IsKeyDown(KEY_LEFT), time_since_epoch - _lastKBUpdate);
    whileRightArrowPressed(IsKeyDown(KEY_RIGHT), time_since_epoch - _lastKBUpdate);
    whileUpArrowPressed(IsKeyDown(KEY_UP), time_since_epoch - _lastKBUpdate);
    whileDownArrowPressed(IsKeyDown(KEY_DOWN), time_since_epoch - _lastKBUpdate);
    whileSpacePressed(IsKeyDown(KEY_SPACE), time_since_epoch - _lastKBUpdate);
    whileEnterPressed(IsKeyDown(KEY_ENTER), time_since_epoch - _lastKBUpdate);

    _lastKBUpdate = time_since_epoch;
}