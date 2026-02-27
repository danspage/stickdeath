#pragma once

#include <string>

class GameImage
{
private:
    int width, height;
    unsigned char *pixels;

public:
    GameImage(std::string filename);

    /// @brief Returns the width of the image, in pixels.
    int getWidth() { return width; }

    /// @brief Returns the height of the image, in pixels.
    int getHeight() { return height; }

    /**
     * @brief Returns the image's pixels. Each pixel will take up 4 indexes,
     * corresponding to the red, green, blue, and alpha channels.
     */
    unsigned char *getPixels() { return pixels; }
};