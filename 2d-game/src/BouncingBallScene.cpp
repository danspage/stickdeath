#include "BouncingBallScene.h"
#include <iostream>

bool BouncingBallScene::DoUpdate()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - lastUpdateTime > 0.1)
    {
        lastUpdateTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return true;
    }
    return false;
}

void BouncingBallScene::Update()
{
    if (DoUpdate())
    {
        yVel++;

        if (x >= 0 && x < widthVoxels)
        {
            prevX = x;
        }
        else
        {
            xVel = 0;
            x = prevX;
        }

        if (y >= 0 && y < heightVoxels)
        {
            prevY = y;
        }
        else
        {
            yVel = 0;
            y = prevY;
        }

        x += xVel;
        y += yVel;
    }
}

void BouncingBallScene::Render(Graphics graphics)
{
    graphics.FillBG(BLACK);

    std::string printText = "Bouncing ball! B) ";

    graphics.DrawString("default", YELLOW, 5, 5, printText);

    graphics.FillVoxel(x, y, colors[colorIndex]);

    std::cout << "X: " << x << " Y: " << y << std::endl;
}

void BouncingBallScene::onEnterPressed()
{
    colorIndex = (colorIndex + 1) % colors.size();
}
