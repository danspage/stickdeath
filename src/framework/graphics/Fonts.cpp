#include "Fonts.h"

#include <cstring>

namespace GameEngine
{
    void _LoadFont(std::string _fileName)
    {
        std::ifstream file(_fileName);
        std::string str;
        int line = 0;

        std::string referenceName;
        int _charHeight;
        std::vector<GameFontChar *> tempCharData;

        while (std::getline(file, str))
        {
            if (line == 0)
            {
                referenceName = str;
            }
            else if (line == 1)
            {
                _charHeight = std::stoi(str);
            }
            else
            {
                std::vector<PixelOffset> lineData;

                size_t pos = str.find(' ');

                if (pos != std::string::npos)
                {
                    std::string first = str.substr(0, pos);
                    std::string second = str.substr(pos + 1);

                    int charWidth = stoi(first);

                    for (int i = 0; i < second.length(); i++)
                    {
                        if (second[i] == '1')
                        {
                            const uint16_t offsetX = static_cast<int>(i) % charWidth;
                            const uint16_t offsetY = static_cast<int>(i) / charWidth;
                            lineData.push_back(PixelOffset({offsetX, offsetY}));
                        }
                        else if (second[i] != '0')
                        {
                            std::cerr << "Invalid characters were present in line " << line << " while loading the font file '" << _fileName << "'!";
                        }
                    }

                    tempCharData.push_back(new GameFontChar(lineData, charWidth));
                }
                else
                {
                    std::cerr << "The font " << _fileName << " is malformed at line " << line << "!" << std::endl;
                    return;
                }
            }
            line++;
        }

        const size_t expectedChars = std::strlen(CHAR_MAP);
        if (tempCharData.size() != expectedChars)
        {
            std::cerr << "Warning: Font '" << referenceName << "' loaded " << tempCharData.size() << " glyphs, expected " << expectedChars << ". Missing characters will render as spaces." << std::endl;
        }

        _fonts[referenceName] = new GameFont(_charHeight, tempCharData);
    }

    int _GetStringWidth(std::string str, std::string font, GameFontRenderOptions options)
    {
        auto fontIt = _fonts.find(font);
        if (fontIt == _fonts.end() || fontIt->second == nullptr)
        {
            return 0;
        }

        GameFont *_font = fontIt->second;
        int numChars = str.size();

        std::vector<GameFontChar *> strChars;

        for (char &c : str)
        {
            strChars.push_back(_font->GetCharData(c));
        }

        int finalWidth = numChars - 1;
        for (GameFontChar *gfc : strChars)
        {
            finalWidth += gfc->getCharWidth();
        }

        return finalWidth;
    };

    void DrawString(std::string str, int x, int y, std::string font, Color color, GameFontRenderOptions options)
    {
        // TODO: implement font render options

        int charX = x;

        auto fontIt = _fonts.find(font);
        if (fontIt == _fonts.end() || fontIt->second == nullptr)
        {
            return;
        }

        GameFont *_font = fontIt->second;
        std::vector<GameFontChar *> strChars;
        strChars.reserve(str.size());

        int strWidth = str.empty() ? 0 : -1;

        for (char &c : str)
        {
            GameFontChar *gfc = _font->GetCharData(c);
            strChars.push_back(gfc);
            strWidth += gfc->getCharWidth() + 1;
        }

        if (options.alignment == CENTER)
        {
            charX -= strWidth / 2;
        }
        else if (options.alignment == RIGHT)
        {
            charX -= strWidth;
        }

        for (GameFontChar *gfc : strChars)
        {
            const std::vector<PixelOffset> &charPx = gfc->getPixels();
            int _charW = gfc->getCharWidth();

            for (const PixelOffset &po : charPx)
            {
                const int drawX = charX + po.x;
                const int drawY = y + po.y;

                if (!IsOnScreen(drawX, drawY))
                {
                    continue;
                }

                FillVoxel(drawX, drawY, color);
            }

            charX += _charW + 1;

            if (charX >= GameEngine::WIDTH_VOXELS)
                return;
        }
    }
}