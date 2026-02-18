#pragma once

class GameState
{
public:
    virtual ~GameState() {};

    virtual void OnLoad() {};
    virtual void onExit() {};
    virtual void Update(float dt) {};
    virtual void Render() {};
    virtual void OnKeyPressed(int key) {};
};