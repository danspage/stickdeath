#pragma once

#include <vector>
#include <algorithm>

#include <raylib.h>

#include "../GameEngine.h"

namespace GameEngine
{
    /// @brief Initializes the graphics engine.
    void InitializeGraphics();

    /// @brief Returns whether a given voxel is within the boundaries of the rendered screen.
    /// @param voxelX Voxel's X coordinate
    /// @param voxelY Voxel's Y coordinate
    bool IsOnScreen(int voxelX, int voxelY);

        /// @brief Fills a pixel (NOT voxel) on the screen with a given color. This should rarely be used in place of `FillVoxel`.
    /// @param pixelX Pixel's X coordinate
    /// @param pixelY Pixel's Y coordinate
    /// @param color Pixel's color
    void FillPixel(int pixelX, int pixelY, Color color);

    /// @brief Fills a pixel (NOT voxel) on the screen with a given color. This should rarely be used in place of `FillVoxel`.
    /// @param pixelX Pixel's X coordinate
    /// @param pixelY Pixel's Y coordinate
    /// @param r Pixel color's red channel value
    /// @param g Pixel color's blue channel value
    /// @param b Pixel color's green channel value
    void FillPixel(int pixelX, int pixelY, uint32_t r, uint32_t g, uint32_t b);

    /// @brief Fills a pixel (NOT voxel) on the screen with a given color. This should rarely be used in place of `FillVoxel`.
    /// @param pixelX Pixel's X coordinate
    /// @param pixelY Pixel's Y coordinate
    /// @param color The color in uint32_t form to fill the pixel with.
    void FillPixel(int pixelX, int pixelY, uint32_t color);

    /// @brief Fills a voxel on the screen with a given color.
    /// @param voxelX Voxel's X coordinate
    /// @param voxelY Voxel's Y coordinate
    /// @param color Voxel's color
    void FillVoxel(int voxelX, int voxelY, Color color);

    /// @brief Fills a voxel on the screen with a given color.
    /// @param voxelX Voxel's X coordinate
    /// @param voxelY Voxel's Y coordinate
    /// @param r Voxel color's red channel value
    /// @param g Voxel color's blue channel value
    /// @param b Voxel color's green channel value
    void FillVoxel(int voxelX, int voxelY, unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    /// @brief Returns the color of the voxel at a given coordinate.
    /// @param voxelX Voxel's X coordinate
    /// @param voxelY Voxel's Y coordinate
    Color GetVoxel(int voxelX, int voxelY);

    /// @brief Fills the entire screen with a given color.
    /// @param color
    void FillBG(Color color);

    /// @brief Fills a rectangular area with a given color.
    /// @param x Top left X coordinate of the rectangle
    /// @param y Top left Y coordinate of the rectangle
    /// @param width Rectangle's width
    /// @param height Rectangle's height
    /// @param color Rectangle's color
    void FillRect(int x, int y, int width, int height, Color color);
}