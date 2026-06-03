#include "LevelLoader.h"

#include "../../../framework/util/StringUtil.h"

#include <fstream>

namespace StickDeath
{
    ParsedLevel LevelLoader::ParseLevel(const std::string &levelName)
    {
        std::ifstream file("assets/data/levels/" + levelName + ".sdlvl");
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open level file: assets/data/levels/" + levelName + ".sdlvl");
        }

        std::string line;

        enum LevelLoaderState
        {
            ReadingHeader,
            ReadingLegend,
            ReadingRows
        };

        LevelLoaderState state = ReadingHeader;

        ParsedLevel parsedLevel;

        bool legendParsed = false, rowsParsed = false;

        while (std::getline(file, line))
        {
            std::string trimmedLine = GameEngine::Util::trim(line);

            if (trimmedLine.empty() || trimmedLine[0] == ';')
            {
                continue;
            }
            else if (trimmedLine == "legend")
            {
                if (legendParsed)
                {
                    throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nDuplicate legend section");
                }
                state = LevelLoaderState::ReadingLegend;
                legendParsed = true;
                continue;
            }
            else if (trimmedLine == "rows")
            {
                if (rowsParsed)
                {
                    throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nDuplicate rows section");
                }
                state = LevelLoaderState::ReadingRows;
                rowsParsed = true;
                continue;
            }

            if (state == ReadingHeader)
            {
                std::vector<std::string_view> splitLine = GameEngine::Util::split(trimmedLine, " ");

                if (splitLine[0] == "version")
                {
                    if (splitLine.size() != 2)
                    {
                        throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nExpected exactly 2 tokens in version line, got " + std::to_string(splitLine.size()));
                    }
                }
                else if (splitLine[0] == "size" || splitLine[0] == "spawn")
                {
                    if (splitLine.size() != 3)
                    {
                        throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nExpected exactly 3 tokens in " + std::string(splitLine[0]) + " line, got " + std::to_string(splitLine.size()));
                    }
                }
                else
                {
                    throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nUnknown header token: " + std::string(splitLine[0]));
                }

                if (splitLine[0] == "version")
                {
                    parsedLevel.version = std::stoi(std::string(splitLine[1]));
                }
                else if (splitLine[0] == "size")
                {
                    parsedLevel.width = std::stoi(std::string(splitLine[1]));
                    parsedLevel.height = std::stoi(std::string(splitLine[2]));
                }
                else if (splitLine[0] == "spawn")
                {
                    parsedLevel.spawnX = std::stoi(std::string(splitLine[1]));
                    parsedLevel.spawnY = std::stoi(std::string(splitLine[2]));
                }
            }

            else if (state == ReadingLegend)
            {
                std::vector<std::string_view> splitLine = GameEngine::Util::split(trimmedLine, " ");

                if (splitLine.size() != 2)
                {
                    throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nExpected exactly 2 tokens in legend line, got " + std::to_string(splitLine.size()));
                }

                if (parsedLevel.legend.find(splitLine[0][0]) != parsedLevel.legend.end())
                {
                    throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nDuplicate legend character: " + std::string(1, splitLine[0][0]));
                }

                if (splitLine[0].length() != 1)
                {
                    throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nLegend character must be a single character, got: " + std::string(splitLine[0]));
                }

                parsedLevel.legend[splitLine[0][0]] = splitLine[1];
            }

            else if (state == ReadingRows)
            {
                if (trimmedLine.length() != parsedLevel.width)
                {
                    throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nExpected row length of " + std::to_string(parsedLevel.width) + ", got " + std::to_string(trimmedLine.length()));
                }

                for (char c : trimmedLine)
                {
                    if (c != '.' && parsedLevel.legend.find(c) == parsedLevel.legend.end())
                    {
                        throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nUnknown legend character in rows: " + std::string(1, c));
                    }
                }

                parsedLevel.rows.push_back(trimmedLine);
            }
        }

        if (parsedLevel.spawnX < 0 || parsedLevel.spawnX >= parsedLevel.width || parsedLevel.spawnY < 0 || parsedLevel.spawnY >= parsedLevel.height)
        {
            throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nSpawn point (" + std::to_string(parsedLevel.spawnX) + ", " + std::to_string(parsedLevel.spawnY) + ") is out of bounds for level size (" + std::to_string(parsedLevel.width) + ", " + std::to_string(parsedLevel.height) + ")");
        }

        if (parsedLevel.rows.size() != parsedLevel.height)
        {
            throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nExpected exactly " + std::to_string(parsedLevel.height) + " rows, got " + std::to_string(parsedLevel.rows.size()));
        }

        if (!legendParsed || !rowsParsed)
        {
            throw std::runtime_error("Invalid level file format: " + levelName + ".sdlvl\nExpected header, legend, and rows sections");
        }

        return parsedLevel;
    }

    void LevelLoader::ApplyLevel(const ParsedLevel &level)
    {
    }
}