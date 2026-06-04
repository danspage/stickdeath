#include "Map.h"

namespace StickDeath::Map
{
    int GetTileX(float worldX)
    {
        return (int)std::floor(worldX);
    }

    int GetTileY(float worldY)
    {
        return (int)std::floor(worldY);
    }

    void SetTile(int x, int y, const std::string &tileName)
    {
        if (!IsInBounds(x, y))
            throw TileOutOfBoundsException(x, y);

        if (tileToTileIndex[y * MAP_WIDTH + x] == NULL_TILE_INDEX)
        {
            tiles.emplace_back(std::make_unique<Tile>(x, y, tileName));
            tileToTileIndex[y * MAP_WIDTH + x] = tiles.size() - 1;
        }
        else
        {
            tiles[tileToTileIndex[y * MAP_WIDTH + x]] = std::make_unique<Tile>(x, y, tileName);
        }
    }

    void SetTile(int x, int y, std::unique_ptr<Tile> tile)
    {
        if (!IsInBounds(x, y))
            throw TileOutOfBoundsException(x, y);

        tile->HardOverwriteCoordinates(x, y);

        if (tileToTileIndex[y * MAP_WIDTH + x] == NULL_TILE_INDEX)
        {
            tiles.emplace_back(std::move(tile));
            tileToTileIndex[y * MAP_WIDTH + x] = tiles.size() - 1;
        }
        else
        {
            tiles[tileToTileIndex[y * MAP_WIDTH + x]] = std::move(tile);
        }
    };

    Tile *TryGetTile(int x, int y)
    {
        if (!IsInBounds(x, y) || tileToTileIndex[y * MAP_WIDTH + x] == NULL_TILE_INDEX)
            return nullptr;

        return tiles[tileToTileIndex[y * MAP_WIDTH + x]].get();
    };

    Tile *TryGetTileAtWorldPos(float worldX, float worldY)
    {
        return TryGetTile(GetTileX(worldX), GetTileY(worldY));
    }

    bool IsInBounds(int x, int y)
    {
        return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
    }

    void ClearMap()
    {
        tiles.clear();
        std::fill(tileToTileIndex.begin(), tileToTileIndex.end(), NULL_TILE_INDEX);
    }

    std::vector<std::pair<int, int>> GetSolidTilesInRow(int y, int startX, int endX)
    {
        std::vector<std::pair<int, int>> matches;

        for (int x = startX; x <= endX; x++)
        {
            Tile *search = TryGetTile(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                matches.push_back({x, y});
            }
        }

        return matches;
    };

    std::vector<std::pair<int, int>> GetSolidTilesInColumn(int x, int startY, int endY)
    {
        std::vector<std::pair<int, int>> matches;

        for (int y = startY; y <= endY; y++)
        {
            Tile *search = TryGetTile(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                matches.push_back({x, y});
            }
        }

        return matches;
    };

    bool CheckSolidTilesExistInRow(int y, int startX, int endX)
    {
        for (int x = startX; x <= endX; x++)
        {
            Tile *search = TryGetTile(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                return true;
            }
        }

        return false;
    };

    bool CheckSolidTilesExistInColumn(int x, int startY, int endY)
    {
        for (int y = startY; y <= endY; y++)
        {
            Tile *search = TryGetTile(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                return true;
            }
        }
        return false;
    };

    void UpdateMap(float dt)
    {
        for (auto &b : tiles)
        {
            b->Update(dt);
        }
    }

    void RenderMap()
    {
        for (auto &b : tiles)
        {
            b->Render();
        }
    }
}