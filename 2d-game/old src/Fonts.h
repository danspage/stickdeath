#pragma once
#include <map>
#include "util/FileUtil.h"
#include "GameFont.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Fonts
{
public:
    void LoadFonts()
    {
        LoadFont("assets/fonts/default.2df", "default");
    };

    std::vector<FontChar> getStringChars(std::string font, std::string str)
    {
        return fonts[font].getStringChars(str);
    }
private:
    std::map<std::string, GameFont> fonts;

    void LoadFont(std::string filename, std::string fontname);
};