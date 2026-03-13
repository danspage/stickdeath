#pragma once

#include <map>

#include "GameImage.h"
#include "Graphics.h"

namespace GameEngine
{
    struct GameImageRenderOptions
    {
        int scaleX = 1;
        int scaleY = 1;
        bool flipHorizontal = false;
        bool flipVertical = false;
    };

    inline std::map<std::string, GameImage *>
        _images;

    /**
     * @brief Used internally within the `GameEngine::LoadAllAssets` function, to load an
     * image into memory.
     * @param referencePath The path that the image will be referenced by for the
     * `GameEngine::GetImage` function. The format is as follows:
     * `assets/animals/mammals/cat.png` becomes `animals/mammals/cat`.
     * @param filePath The path of the file, starting with `assets/...`
     */
    inline void _LoadImage(std::string referencePath, std::string filePath)
    {
        _images[referencePath] = new GameImage(filePath);
    };

    /**
     * @brief Returns a game image from memory.
     * @param imageName The path of the image. The format is as follows:
     * `assets/animals/mammals/cat.png` becomes `animals/mammals/cat` for the parameter.
     * @return The GameImage retrieved from memory.
     */
    GameImage *GetImage(std::string imageName)
    {
        return _images[imageName];
    }

    /**
     * @brief Draws an image from memory to the screen.
     * @param imageName The path of the image. The format is as follows:
     * `assets/animals/mammals/cat.png` becomes `animals/mammals/cat` for the parameter.
     * @param x The x coordinate of the top left of the image.
     * @param y The y coordinate of the top left of the image.
     * @param options Additional options to influence the image's rendering.
     */
    void DrawImage(std::string imageName, int x, int y, GameImageRenderOptions options = {});
}