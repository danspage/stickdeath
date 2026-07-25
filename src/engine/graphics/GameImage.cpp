#include "GameImage.h"

#include <string>
#include <cstring>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace GameEngine
{
    GameImage::GameImage(std::string filename)
    {
        SDL_Surface *loaded = IMG_Load(filename.c_str());
        if (loaded == nullptr)
        {
            throw std::runtime_error("IMG_Load failed for '" + filename + "': " + IMG_GetError());
            width = 1;
            height = 1;
            pixels = new unsigned char[4]{0, 0, 0, 0};
            return;
        }

        SDL_Surface *rgba = SDL_ConvertSurfaceFormat(loaded, SDL_PIXELFORMAT_RGBA32, 0);
        SDL_FreeSurface(loaded);

        if (rgba == nullptr)
        {
            throw std::runtime_error("SDL_ConvertSurfaceFormat failed for '" + filename + "': " + SDL_GetError());
            width = 1;
            height = 1;
            pixels = new unsigned char[4]{0, 0, 0, 0};
            return;
        }

        width = rgba->w;
        height = rgba->h;

        pixels = new unsigned char[width * height * 4];
        std::memcpy(pixels, rgba->pixels, static_cast<size_t>(width) * static_cast<size_t>(height) * 4);

        SDL_FreeSurface(rgba);
    }
}