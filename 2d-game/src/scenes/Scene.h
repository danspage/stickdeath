#pragma once
#include <string>   
#include <functional>
#include "../Graphics.h"

class Scene
{
public:
    virtual ~Scene() {};
    virtual void onEnter() {};
    virtual void onExit() {};
    virtual void Render(Graphics* graphics) {};
    virtual void Update() {};
    virtual void onLeftArrowPressed() {};
    virtual void whileLeftArrowPressed(bool pressed, double dt) {};
    virtual void onRightArrowPressed() {};
    virtual void whileRightArrowPressed(bool pressed, double dt) {};
    virtual void onUpArrowPressed() {};
    virtual void whileUpArrowPressed(bool pressed, double dt) {};
    virtual void onDownArrowPressed() {};
    virtual void whileDownArrowPressed(bool pressed, double dt) {};
    virtual void onSpacePressed() {};
    virtual void whileSpacePressed(bool pressed, double dt) {};
    virtual void onEnterPressed() {};
    virtual void whileEnterPressed(bool pressed, double dt) {};
    void DoKeyboardInput();
};