#include "Fonts.h"
#include "util/FileUtil.h"
#include <fstream>
#include <string>
#include "Constants.h"
#include "GameFont.h"

void Fonts::LoadFont(std::string filename, std::string fontname)
{
    std::ifstream file(filename);
    std::string str;
    int line = 0;

    std::vector<std::vector<int>> chars;
    int charWidth, charHeight;

    while (std::getline(file, str))
    {
        if (line == 0)
        {
            charWidth = std::stoi(str);
        }
        else if (line == 1)
        {
            charHeight = std::stoi(str);
        }
        else
        {
            std::vector<int> lineData;

            for (char c : str)
            {
                if (std::isdigit(c))
                {
                    lineData.push_back(c - '0');
                }
            }

            chars.push_back(lineData);
        }
        line++;
    }

    fonts.try_emplace(fontname, GameFont(charWidth, charHeight, chars));
}