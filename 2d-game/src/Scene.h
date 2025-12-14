#pragma once
#include <string>   
#include <functional>
#include "Graphics.h"

class Scene
{
public:
    virtual void Render(Graphics graphics);
    virtual void Update();
    virtual void onLeftArrowPressed() {};
    virtual void whileLeftArrowPressed(bool pressed) {};
    virtual void onRightArrowPressed() {};
    virtual void whileRightArrowPressed(bool pressed) {};
    virtual void onUpArrowPressed() {};
    virtual void whileUpArrowPressed(bool pressed) {};
    virtual void onDownArrowPressed() {};
    virtual void whileDownArrowPressed(bool pressed) {};
    virtual void onSpacePressed() {};
    virtual void whileSpacePressed(bool pressed) {};
    virtual void onEnterPressed() {};
    virtual void whileEnterPressed(bool pressed) {};
    void DoKeyboardInput();
};