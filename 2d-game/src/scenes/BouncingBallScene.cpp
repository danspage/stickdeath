#include "BouncingBallScene.h"
#include "../Graphics.h"
#include "../Constants.h"
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

void BouncingBallScene::Render(Graphics* graphics)
{
    graphics->FillBG(WHITE);

    graphics->DrawImage("large_dialogue", widthVoxels/2, heightVoxels/2, true, true);

    std::string printText = "Bouncing ball! B) ";

    graphics->DrawString("default", colors[colorIndex], 5, 5, printText);

    // graphics->FillRect(x-1, y-1, 3, 3, colors[colorIndex]);
    graphics->DrawImage("player", x, y, true, true);
}

void BouncingBallScene::onEnterPressed()
{
    colorIndex = (colorIndex + 1) % colors.size();
}
