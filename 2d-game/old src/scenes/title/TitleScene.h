#pragma once
#include "../Scene.h"

class TitleScene : public Scene
{
public:
    TitleScene() : Scene() {}
    void Render(Graphics* graphics, SceneManager* sm) override;
    void Update(SceneManager* sm) override;
    void onUpArrowPressed() override;
    void onDownArrowPressed() override;
    void onEnterPressed() override;
private:
    std::vector<std::string> options = {"Play", "Settings", "Quit Game"};
    int optionsIndex = 0;
};