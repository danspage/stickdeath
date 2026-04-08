#include "Block.h"

#include "Blocks.h"
#include "../Map.h"
#include "../../../../framework/graphics/Images.h"
#include "../../entity/Entity.h"

namespace StickDeath
{
    Block::Block(int xPos, int yPos, std::string blockName)
        : x(xPos), y(yPos),
          texturePath(_defaultBlockProperties.at(blockName).texturePath),
          properties(_defaultBlockProperties.at(blockName).properties)
    {
    }

    void Block::HardOverwriteCoordinates(int xPos, int yPos)
    {
        x = xPos;
        y = yPos;
    }

    BlockProperties Block::GetProperties() const
    {
        return properties;
    }

    void Block::Render()
    {
        int drawX = x * StickDeath::Map::TILE_SIZE;
        int drawY = GameEngine::HEIGHT_VOXELS - (y + 1) * StickDeath::Map::TILE_SIZE;

        GameEngine::DrawImage(texturePath, drawX, drawY);
    }
}