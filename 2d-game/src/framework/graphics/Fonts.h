#pragma once

#include <limits>
#include <map>

#include "GameFont.h"

namespace GameEngine
{
    enum GameFontAlignment
    {
        LEFT,
        RIGHT,
        CENTER,
    };

    struct GameFontRenderOptions
    {
        GameFontAlignment alignment = LEFT;
        int scale = 1;
        unsigned int wrapWidth = std::numeric_limits<int>::max();
    };

    inline std::map<std::string, GameFont*> _fonts;

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
}