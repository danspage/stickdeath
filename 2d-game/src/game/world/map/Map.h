#pragma once

#include <vector>
#include <deque>
#include <format>

#include "block/Block.h"

namespace StickDeath::Map
{
    const int TILE_SIZE = 16;

    class BlockOutOfBoundsException : public std::exception
    {
    private:
        std::string message;

    public:
        BlockOutOfBoundsException(int _x, int _y)
        {
            message = std::format("The coordinate ({}, {}) is outside of the map", _x, _y);
        }
        const char *what() const noexcept
        {
            return message.c_str();
        }
    };

    inline const int MAP_WIDTH = 10000, MAP_HEIGHT = 300;

    inline std::vector<int> tileToBlockIndex((MAP_WIDTH * MAP_HEIGHT), -1);
    inline std::deque<Block> blocks;

    int GetTileX(float worldX);
    int GetTileY(float worldY);

    void SetBlock(int x, int y, const std::string &blockName);
    void SetBlock(int x, int y, const Block &block);
    Block *TryGetBlock(int x, int y);
    Block *TryGetBlockAtWorldPos(float worldX, float worldY);
    bool IsInBounds(int x, int y);

    void Render();
}