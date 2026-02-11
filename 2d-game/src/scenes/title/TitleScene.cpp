#include "TitleScene.h"
#include "../../Constants.h"

void TitleScene::Render(Graphics *graphics, SceneManager *sm)
{
    graphics->FillBG(SKYBLUE);

    graphics->FillRect(50, heightVoxels / 2 - 35, widthVoxels - 100, 20, LIGHTGRAY);
    graphics->DrawString("default", optionsIndex == 0 ? RED : YELLOW, widthVoxels / 2, heightVoxels / 2 - 28, "Play", true);

    graphics->FillRect(50, heightVoxels / 2 - 10, widthVoxels - 100, 20, LIGHTGRAY);
    graphics->DrawString("default", optionsIndex == 1 ? RED : YELLOW, widthVoxels / 2, heightVoxels / 2 - 3, "Options", true);

    graphics->FillRect(50, heightVoxels / 2 + 15, widthVoxels - 100, 20, LIGHTGRAY);
    graphics->DrawString("default", optionsIndex == 2 ? RED : YELLOW, widthVoxels / 2, heightVoxels / 2 + 22, "Exit Game", true);
}

void TitleScene::Update(SceneManager *sm)
{
}

void TitleScene::onUpArrowPressed()
{
    optionsIndex -= 1;
    if (optionsIndex < 0)
        optionsIndex = 2;
}

void TitleScene::onDownArrowPressed()
{
    optionsIndex += 1;
    if (optionsIndex > 2)
        optionsIndex = 0;
}

void TitleScene::onEnterPressed()
{
    if (optionsIndex == 0)
    {
        
    }
}
