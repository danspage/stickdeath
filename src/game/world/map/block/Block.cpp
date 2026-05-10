#include "Block.h"

#include "Blocks.h"
#include "../Map.h"
#include "../../../../framework/graphics/Images.h"
#include "../../entity/Entity.h"
#include "../../../../framework/GameEngine.h"
#include "../../../../framework/graphics/camera/Camera.h"

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
        const float worldLeft = static_cast<float>(x * StickDeath::Map::TILE_SIZE);
        const float worldTop = static_cast<float>((y + 1) * StickDeath::Map::TILE_SIZE);

        const PointI screen = StickDeath::Camera::WorldToScreen({worldLeft, worldTop});
        GameEngine::DrawImage(texturePath, screen.x, screen.y);
    }
}