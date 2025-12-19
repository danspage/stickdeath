#include "BouncingBallScene.h"
#include "../Graphics.h"
#include "../Constants.h"
#include <iostream>

// auto _now = std::chrono::system_clock::now();

// bool BouncingBallScene::DoUpdate()
// {
//     // if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - lastUpdateTime > 0.1)
//     // {
//     //     lastUpdateTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//     //     return true;
//     // }
//     // return false;
// }

void BouncingBallScene::Update()
{
    // std::chrono::duration<double> seconds = _now.time_since_epoch();
    // double time_since_epoch = seconds.count();

    // if (DoUpdate())
    // {
    //     yVel++;

    //     if (x >= 0 && x < widthVoxels)
    //     {
    //         prevX = x;
    //     }
    //     else
    //     {
    //         xVel = 0;
    //         x = prevX;
    //     }

    //     if (y >= 0 && y < heightVoxels)
    //     {
    //         prevY = y;
    //     }
    //     else
    //     {
    //         yVel = 0;
    //         y = prevY;
    //     }

    //     x += xVel;
    //     y += yVel;
    // }
}

void BouncingBallScene::Render(Graphics *graphics)
{
    graphics->FillBG(BLACK);

    graphics->DrawImage("large_dialogue", widthVoxels / 2, heightVoxels / 2, true, true);

    std::string printText = "Bouncing ball! B) ";

    graphics->DrawString("default", colors[colorIndex], 5, 5, printText);

    // graphics->FillRect(x-1, y-1, 3, 3, colors[colorIndex]);
    graphics->DrawImage("smiley", x, y, true, true);
    graphics->DrawImage("smiley", 30, 30, false, false);

    player.render(graphics);
}

void BouncingBallScene::onEnterPressed()
{
    colorIndex = (colorIndex + 1) % colors.size();
}

void BouncingBallScene::whileLeftArrowPressed(bool pressed, double dt)
{
    if (pressed)
    {
        std::cout << "Pressing left! " << dt << std::endl;
        player.moveLeft(dt);
    }
}

void BouncingBallScene::whileRightArrowPressed(bool pressed, double dt)
{
    if (pressed)
    {
        std::cout << "Pressing right! " << dt << std::endl;
        player.moveRight(dt);
    }
}