#include "Tile.h"

#include "Tiles.h"
#include "../Map.h"
#include "../../../../framework/graphics/Images.h"
#include "../../entity/Entity.h"
#include "../../../../framework/GameEngine.h"
#include "../../../../framework/graphics/camera/Camera.h"

namespace StickDeath
{
    Tile::Tile(int xPos, int yPos, std::string tileName)
        : x(xPos), y(yPos),
          texturePath(_defaultTileProperties.at(tileName).texturePath),
          properties(_defaultTileProperties.at(tileName).properties)
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

        const PointI screen = StickDeath::Camera::WorldToScreen({worldLeft, worldTop});
        GameEngine::DrawImage(texturePath, screen.x, screen.y);
    }
}