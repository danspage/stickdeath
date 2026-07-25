#pragma once

#include <string>

namespace GameEngine
{
    class GameImage
    {
    private:
        int width = 0, height = 0;
        unsigned char *pixels = nullptr;

    public:
        GameImage(int width, int height, unsigned char &pixels)
            : width(width), height(height), pixels(&pixels) {}

        GameImage(std::string filename);

        /// @brief Returns the width of the image, in pixels.
        int getWidth() const { return width; }

        /// @brief Returns the height of the image, in pixels.
        int getHeight() const { return height; }

        /**
         * @brief Returns the image's pixels. Each pixel will take up 4 indexes,
         * corresponding to the red, green, blue, and alpha channels.
         */
        const unsigned char *getPixels() const { return pixels; }
    };
}