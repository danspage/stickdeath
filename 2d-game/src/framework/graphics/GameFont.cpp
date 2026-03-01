#include "GameFont.h"

namespace GameEngine
{
    GameFont::GameFont(int _charWidth, int _charHeight, std::vector<bool> _fontChars)
    {
        charWidth = _charWidth;
        charHeight = _charHeight;
        fontChars = _fontChars;
    }

    std::vector<bool> GameFont::GetCharData(char c)
    {
        // May be a point of issue, verify that this works
        int indexOfChar = (int)(strchr(CHAR_MAP, c) - CHAR_MAP) * charWidth * charHeight;

        return {fontChars.begin() + indexOfChar, fontChars.begin() + indexOfChar + charWidth * charHeight};
    }
}