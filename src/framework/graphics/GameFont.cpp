#include "GameFont.h"

#include <cstring>

namespace GameEngine
{
    GameFont::GameFont(int _charHeight, std::vector<GameFontChar*> _fontChars)
    {
        charHeight = _charHeight;
        fontChars = _fontChars;
    }

    GameFontChar* GameFont::GetCharData(char c)
    {
        static GameFontChar emptyChar({}, 0);

        if (fontChars.empty())
        {
            return &emptyChar;
        }

        const char *mappedChar = std::strchr(CHAR_MAP, c);
        if (mappedChar == nullptr)
        {
            return fontChars[0];
        }

        const size_t indexOfChar = static_cast<size_t>(mappedChar - CHAR_MAP);
        if (indexOfChar >= fontChars.size())
        {
            return fontChars[0];
        }

        return fontChars[indexOfChar];
    }
}