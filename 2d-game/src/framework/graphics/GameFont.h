#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace GameEngine
{
    inline const char* CHAR_MAP = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    class GameFont
    {
    private:
        std::vector<bool> fontChars;
        int charWidth, charHeight;
    public:
        GameFont(int _charWidth, int _charHeight, std::vector<bool> _fontChars);
        std::vector<bool> GetCharData(char c);
    };
}