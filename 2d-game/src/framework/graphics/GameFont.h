#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace GameEngine
{
    inline const char *CHAR_MAP = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    class GameFontChar
    {
    private:
        std::vector<bool> pixels;
        int charWidth;

    public:
        GameFontChar(std::vector<bool> _pixels, int _charWidth)
        {
            pixels = _pixels;
            charWidth = _charWidth;
        };
        const std::vector<bool> &getPixels() const { return pixels; };
        int getCharWidth() { return charWidth; };
    };

    class GameFont
    {
    private:
        std::vector<GameFontChar *> fontChars;
        int charHeight;

    public:
        GameFont(int _charHeight, std::vector<GameFontChar *> _fontChars);
        GameFontChar *GetCharData(char c);
        int GetStrWidthVoxels();
        int GetCharHeight() { return charHeight; }
    };
}