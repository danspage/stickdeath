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

    void SetBlock(int x, int y, const std::string &blockName)
    {
        if (!IsInBounds(x, y))
            throw BlockOutOfBoundsException(x, y);

        if (tileToBlockIndex[y * MAP_WIDTH + x] == -1)
        {
            blocks.emplace_back(Block(x, y, blockName));
            tileToBlockIndex[y * MAP_WIDTH + x] = blocks.size() - 1;
        }
        else
        {
            blocks[tileToBlockIndex[y * MAP_WIDTH + x]] = Block(x, y, blockName);
        }
    }

    void SetBlock(int x, int y, const Block &block)
    {
        if (!IsInBounds(x, y))
            throw BlockOutOfBoundsException(x, y);

        Block adjustedBlock = block;
        adjustedBlock.HardOverwriteCoordinates(x, y);

        if (tileToBlockIndex[y * MAP_WIDTH + x] == -1)
        {
            blocks.emplace_back(adjustedBlock);
            tileToBlockIndex[y * MAP_WIDTH + x] = blocks.size() - 1;
        }
        else
        {
            blocks[tileToBlockIndex[y * MAP_WIDTH + x]] = adjustedBlock;
        }
    };

    Block *TryGetBlock(int x, int y)
    {
        if (!IsInBounds(x, y) || tileToBlockIndex[y * MAP_WIDTH + x] == -1)
            return nullptr;

        return &blocks[tileToBlockIndex[y * MAP_WIDTH + x]];
    };

    Block *TryGetBlockAtWorldPos(float worldX, float worldY)
    {
        return TryGetBlock(GetTileX(worldX), GetTileY(worldY));
    }

    bool IsInBounds(int x, int y)
    {
        return (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT);
    }

    std::vector<std::pair<int, int>> GetSolidBlocksInRow(int y, int startX, int endX)
    {
        std::vector<std::pair<int, int>> matches;

        for (int x = startX; x <= endX; x++)
        {
            Block *search = TryGetBlock(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                matches.push_back({x, y});
            }
        }

        return matches;
    };

    std::vector<std::pair<int, int>> GetSolidBlocksInColumn(int x, int startY, int endY)
    {
        std::vector<std::pair<int, int>> matches;

        for (int y = startY; y <= endY; y++)
        {
            Block *search = TryGetBlock(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                matches.push_back({x, y});
            }
        }

        return matches;
    };

    bool CheckSolidBlocksExistInRow(int y, int startX, int endX)
    {
        for (int x = startX; x <= endX; x++)
        {
            Block *search = TryGetBlock(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                return true;
            }
        }

        return false;
    };

    bool CheckSolidBlocksExistInColumn(int x, int startY, int endY)
    {
        for (int y = startY; y <= endY; y++)
        {
            Block *search = TryGetBlock(x, y);
            if (search != nullptr && search->GetProperties().isSolid)
            {
                return true;
            }
        }
        return false;
    };

    void UpdateMap(float dt)
    {
        for (Block &b : blocks)
        {
            b.Update(dt);
        }
    }

    void RenderMap()
    {
        for (Block &b : blocks)
        {
            b.Render();
        }
    }
}