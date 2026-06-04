#pragma once

#include <vector>
#include <deque>
#include <format>
#include <memory>
#include <cmath>

#include "tile/Tile.h"

namespace StickDeath::Map
{
    const inline int TILE_SIZE = 16;

    const inline float EPSILON = 0.0001;

    class TileOutOfBoundsException : public std::exception
    {
    private:
        std::string message;

    public:
        TileOutOfBoundsException(int _x, int _y)
        {
            message = std::format("The coordinate ({}, {}) is outside of the map", _x, _y);
        }
        const char *what() const noexcept
        {
            return message.c_str();
        }
    };

    inline const int MAP_WIDTH = 10000, MAP_HEIGHT = 300;

    inline const float GRAVITY = -25;

    const inline int NULL_TILE_INDEX = -1;
    inline std::vector<int> tileToTileIndex((MAP_WIDTH * MAP_HEIGHT), NULL_TILE_INDEX);
    inline std::deque<std::unique_ptr<Tile>> tiles;

    int GetTileX(float worldX);
    int GetTileY(float worldY);

    void SetTile(int x, int y, const std::string &tileName);
    void SetTile(int x, int y, const std::unique_ptr<Tile> tile);
    Tile *TryGetTile(int x, int y);
    Tile *TryGetTileAtWorldPos(float worldX, float worldY);
    bool IsInBounds(int x, int y);

    void ClearMap();

    std::vector<std::pair<int, int>> GetSolidTilesInRow(int y, int startX, int endX);
    std::vector<std::pair<int, int>> GetSolidTilesInColumn(int x, int startY, int endY);

    bool CheckSolidTilesExistInRow(int y, int startX, int endX);
    bool CheckSolidTilesExistInColumn(int x, int startY, int endY);

    void UpdateMap(float dt);
    void RenderMap();
}