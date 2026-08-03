#include "Tile.h"

#include "Tiles.h"
#include "../Map.h"
#include "../../entity/Entity.h"
#include "../../../../engine/GameEngine.h"
#include "../../../../engine/graphics/camera/Camera.h"
#include "../../../../engine/graphics/textures/TextureManager.h";
#include <Images.h>

namespace StickDeath
{
    Tile::Tile(int xPos, int yPos, std::string tileName)
        : x(xPos), y(yPos),
          properties(_defaultTileProperties.at(tileName))
    {
    }

    void Tile::HardOverwriteCoordinates(int xPos, int yPos)
    {
        x = xPos;
        y = yPos;
    }

    TileProperties Tile::GetProperties() const
    {
        return properties;
    }

    void Tile::Render()
    {
        const float worldLeft = static_cast<float>(x * StickDeath::Map::TILE_SIZE_VOXELS);
        const float worldTop = static_cast<float>((y + 1) * StickDeath::Map::TILE_SIZE_VOXELS);

        const GameEngine::PointI screen = StickDeath::Camera::WorldToScreen({worldLeft, worldTop});

        // if (properties.animated)
        // {
        //     // GameEngine::DrawImage(properties.texturePaths[_animationStates.at(properties.id).currentFrame], screen.x, screen.y);
        //     GameEngine::DrawImage(GameEngine::TextureManager::GetTexture(properties.texture), screen.x, screen.y);
        // }
        // else
        // {
        //     // GameEngine::DrawImage(properties.texturePaths[0], screen.x, screen.y);
        // }

        GameEngine::DrawImage(GameEngine::TextureManager::GetTexture(properties.texture), screen.x, screen.y);
    }
}