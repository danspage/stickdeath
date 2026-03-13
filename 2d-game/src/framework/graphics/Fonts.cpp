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
        int _charWidth, _charHeight;
        std::vector<bool> tempCharData;

        while (std::getline(file, str))
        {
            if (line == 0)
            {
                referenceName = str;
            }
            else if (line == 1)
            {
                _charWidth = std::stoi(str);
            }
            else if (line == 2)
            {
                _charHeight = std::stoi(str);
            }
            else
            {
                std::vector<bool> lineData;

                for (char c : str)
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

                tempCharData.insert(tempCharData.end(), lineData.begin(), lineData.end());
            }
            line++;
        }

        _fonts[referenceName] = new GameFont(_charWidth, _charHeight, tempCharData);
    }

    void DrawString(std::string str, std::string font, int x, int y, Color color, GameFontRenderOptions options)
    {
        // TODO: implement font render options

        int charX = x;

        GameFont *_font = _fonts[font];

        int charW = _font->GetCharWidth();

        int strWidthPx = (str.size() * charW) + (str.size() - 1);
        if (options.alignment == CENTER)
        {
            charX -= strWidthPx / 2;
        }
        else if (options.alignment == RIGHT)
        {
            charX -= strWidthPx;
        }

        for (char &c : str)
        {
            std::vector<bool> charData = _font->GetCharData(c);
            for (int i = 0; i < charData.size(); i++)
            {
                if (charData[i])
                {
                    int pxX = charX + (i % charW);
                    int pxY = y + (i / charW);

                    FillVoxel(pxX, pxY, color);
                }
            }

            charX += charW + 1;
        }
    }
}