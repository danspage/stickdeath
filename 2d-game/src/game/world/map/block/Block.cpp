#include "Block.h"

#include "Blocks.h"
#include "../Map.h"
#include "../../../../framework/graphics/Images.h"

namespace StickDeath
{
    Block::Block(int xPos, int yPos, std::string blockName)
    {
        x = xPos;
        y = yPos;

        // TODO error: key not found for some reason
        texturePath = _defaultBlockProperties.at(blockName).at("texture");
    }

    void Block::HardOverwriteCoordinates(int xPos, int yPos)
    {
        x = xPos;
        y = yPos;
    }

    void Block::Render()
    {
        int drawX = x * StickDeath::Map::TILE_SIZE;
        int drawY = GameEngine::HEIGHT_VOXELS - (y + 1) * StickDeath::Map::TILE_SIZE;

        GameEngine::DrawImage(texturePath, drawX, drawY);
    }
}