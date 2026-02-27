#pragma once

#include <map>

#include "GameImage.h"
#include "Graphics.h"

namespace GameEngine
{
    struct GameImageOptions
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
     * @param filePath the path of the file, starting with `assets/...`
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
    inline GameImage *GetImage(std::string imageName)
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
    inline void DrawImage(std::string imageName, int x, int y, GameImageOptions options = {})
    {
        GameImage *img = GetImage(imageName);
        unsigned char *imgPx = img->getPixels();

        int xOffset = 0, yOffset = 0, xMult = 1, yMult = 1;
        if (options.flipHorizontal)
        {
            xOffset += img->getWidth()-1;
            xMult = -1;
        }
        if (options.flipVertical)
        {
            yOffset += img->getHeight()-1;
            yMult = -1;
        }

        for (int imgX = 0; imgX < img->getWidth(); imgX++)
        {
            for (int imgY = 0; imgY < img->getHeight(); imgY++)
            {
                int imgIndex = (imgY * img->getWidth() + imgX) * 4;
                if (imgPx[imgIndex + 3] != 0)
                {
                    int drawX = x + imgX * xMult + xOffset;
                    int drawY = y + imgY * yMult + yOffset;
                    if (IsOnScreen(drawX, drawY))
                    {
                        FillVoxel(drawX, drawY, imgPx[imgIndex], imgPx[imgIndex + 1], imgPx[imgIndex + 2], imgPx[imgIndex + 3]);
                    }
                }
            }
        }
    }
}