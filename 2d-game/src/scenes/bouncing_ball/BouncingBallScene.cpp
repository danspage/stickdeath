#include "BouncingBallScene.h"
#include "../../Graphics.h"
#include "../../Constants.h"
#include <iostream>
#include "RectBlock.h"

RectBlock blocks[] = {
    // Fill around screen borders for collision
    RectBlock(0, -11, widthVoxels, 10),
    RectBlock(0, heightVoxels, widthVoxels, 10),
    RectBlock(-11, 0, 10, heightVoxels),
    RectBlock(widthVoxels, 0, 10, heightVoxels),

    RectBlock(100, 100, 20, 20),
};

void BouncingBallScene::onEnter()
{
    player.setXPos(20);
    player.setYPos(20);
}

void BouncingBallScene::Update(SceneManager *sm)
{
    for (RectBlock b : blocks)
    {
        player.doCollision(&b);
    }
}

void BouncingBallScene::Render(Graphics *graphics, SceneManager *sm)
{
    graphics->FillBG(BLACK);

    graphics->DrawImage("large_dialogue", widthVoxels / 2, heightVoxels / 2, true, true);

    std::string printText = "Bouncing ball! B) ";

    graphics->DrawString("default", colors[colorIndex], 5, 5, printText);

    graphics->DrawImage("smiley", x, y, true, true);
    graphics->DrawImage("smiley", 30, 30, false, false);

    player.render(graphics);

    for (RectBlock b : blocks)
    {
        b.render(graphics);
    }
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

void BouncingBallScene::whileUpArrowPressed(bool pressed, double dt)
{
    if (pressed)
    {
        std::cout << "Pressing up! " << dt << std::endl;
        player.moveUp(dt);
    }
}

void BouncingBallScene::whileDownArrowPressed(bool pressed, double dt)
{
    if (pressed)
    {
        std::cout << "Pressing down! " << dt << std::endl;
        player.moveDown(dt);
    }
}