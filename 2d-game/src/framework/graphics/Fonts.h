#pragma once

#include <limits>
#include <map>

#include <raylib.h>

#include "GameFont.h"
#include "Graphics.h"
#include "../GameEngine.h"

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

    inline std::map<std::string, GameFont *> _fonts;

    /**
     * @brief Used internally within the `GameEngine::LoadAllAssets` function, to load a
     * font into memory.
     * @param referenceName The name that the font will be referenced as when retrieved
     * by various functions.
     * @param filePath The path of the file, starting with `assets/...`
     */
    void _LoadFont(std::string _fileName);

    int _GetStringWidth(std::string str, std::string font, GameFontRenderOptions options = {});

    /**
     * @brief Draws a string onto the screen.
     * @param str The string to be drawn.
     * @param x The x coordinate to draw the string at.
     * @param y The y coordinate to draw the string at.
     * @param font The name of the font, as written in the first line of the font's asset file.
     * @param color The color of the text.
     * @param options Additional options to modify the rendering of the font.
     */
    void DrawString(std::string str, int x, int y, std::string font, Color color, GameFontRenderOptions options = {});
}