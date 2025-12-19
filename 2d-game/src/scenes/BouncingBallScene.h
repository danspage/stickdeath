#pragma once
#include "Scene.h"
#include <raylib.h>
#include "Player.h"

class BouncingBallScene : public Scene
{
public:
    BouncingBallScene() : Scene() {}
    void Render(Graphics* graphics) override;
    void Update() override;
    void onEnterPressed() override;
    void onUpArrowPressed() override { yVel = std::min(yVel, -10); };
    void whileLeftArrowPressed(bool pressed, double dt) override;
    void whileRightArrowPressed(bool pressed, double dt) override;
private:
    // bool DoUpdate();
    long lastUpdateTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int x = 20, y = 20;
    int xVel = 0, yVel = 0;
    int maxXVel = 10, maxYVel = 10;
    int prevX = x, prevY = y;
    int colorIndex = 0;
    std::vector<Color> colors = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, VIOLET };
    Player player = Player();
};