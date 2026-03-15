#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace GameEngine
{
    inline const char *CHAR_MAP = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";

    struct PixelOffset
    {
        uint16_t x;
        uint16_t y;
    };

    class GameFontChar
    {
    private:
        std::vector<PixelOffset> pixels;
        uint8_t charWidth;

    public:
        GameFontChar(std::vector<PixelOffset> _pixels, uint8_t _charWidth)
        {
            pixels = _pixels;
            charWidth = _charWidth;
        };
        const std::vector<PixelOffset> &getPixels() const { return pixels; };
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
        int GetCharHeight() { return charHeight; }
    };
}