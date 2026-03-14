#include "GameFont.h"

namespace GameEngine
{
    GameFont::GameFont(int _charHeight, std::vector<GameFontChar*> _fontChars)
    {
        charHeight = _charHeight;
        fontChars = _fontChars;
    }

    GameFontChar* GameFont::GetCharData(char c)
    {
        int indexOfChar = (int)(strchr(CHAR_MAP, c) - CHAR_MAP);
        return fontChars[indexOfChar];
    }
}