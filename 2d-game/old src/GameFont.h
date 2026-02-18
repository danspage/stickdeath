#pragma once
#include <vector>
#include "Constants.h"
#include <iostream>

struct FontChar
{
    int width;
    int height;
    std::vector<int> pixels;
};

class GameFont
{
public:
    GameFont(){};
    GameFont(int _charWidth, int _charHeight, std::vector<std::vector<int>> _chars)
    {
        charWidth = _charWidth;
        charHeight = _charHeight;
        chars = _chars;
    };
    std::vector<FontChar> getStringChars(std::string str)
    {
        std::vector<FontChar> strChars;

        int charCount = 0;
        for (char &c : str)
        {
            std::string::size_type charIndex = CHAR_MAP.find(c);

            if (charIndex != std::string::npos)
            {
                int intIndex = static_cast<int>(charIndex); // FONT_MAP index of char
                FontChar fontChar;
                fontChar.pixels = chars[intIndex];
                fontChar.width = charWidth;
                fontChar.height= charHeight;
                strChars.push_back(fontChar);
            }
            else
            {
                std::cerr << "The character " << c << " is not a valid font character!";
            }

            charCount ++;
        }

        return strChars;
    }

private:
    int charWidth, charHeight;
    std::vector<std::vector<int>> chars;
};