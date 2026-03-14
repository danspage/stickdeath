#include "Fonts.h"

namespace GameEngine
{
    /**
     * @brief Used internally within the `GameEngine::LoadAllAssets` function, to load a
     * font into memory.
     * @param referenceName The name that the font will be referenced as when retrieved
     * by various functions.
     * @param filePath The path of the file, starting with `assets/...`
     */
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
                std::vector<bool> lineData;

                size_t pos = str.find(' ');

                if (pos != std::string::npos)
                {
                    std::string first = str.substr(0, pos);
                    std::string second = str.substr(pos + 1);

                    for (char c : second)
                    {
                        if (c == '0')
                        {
                            lineData.push_back(false);
                        }
                        else if (c == '1')
                        {
                            lineData.push_back(true);
                        }
                        else
                        {
                            std::cerr << "Invalid characters were present in line " << line << " while loading the font file '" << _fileName << "'!";
                        }
                    }

                    tempCharData.push_back(new GameFontChar(lineData, stoi(first)));
                }
                else
                {
                    std::cerr << "The font " << _fileName << " is malformed at line " << line << "!" << std::endl;
                    return;
                }
            }
            line++;
        }

        _fonts[referenceName] = new GameFont(_charHeight, tempCharData);
    }

    int _GetStringWidth(std::string str, std::string font, GameFontRenderOptions options)
    {
        GameFont *_font = _fonts[font];
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

        GameFont *_font = _fonts[font];
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
            const std::vector<bool> &charPx = gfc->getPixels();
            int _charW = gfc->getCharWidth();
            int _charH = charPx.size() / _charW;

            for (int row = 0; row < _charH; row++)
            {
                int pxY = y + row;
                if (pxY < 0 || pxY >= GameEngine::HEIGHT_VOXELS)
                {
                    continue;
                }

                int rowStart = row * _charW;
                for (int col = 0; col < _charW; col++)
                {
                    if (!charPx[rowStart + col])
                    {
                        continue;
                    }

                    int pxX = charX + col;
                    if (pxX < 0 || pxX >= GameEngine::WIDTH_VOXELS)
                    {
                        continue;
                    }

                    FillVoxel(pxX, pxY, color);
                }
            }

            charX += _charW + 1;

            if (charX >= GameEngine::WIDTH_VOXELS)
                return;
        }
    }
}