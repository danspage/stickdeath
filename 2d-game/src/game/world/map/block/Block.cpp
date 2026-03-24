#include "Block.h"

#include "Blocks.h"
#include "../../../../framework/graphics/Images.h"

namespace StickDeath {
    Block::Block(int xPos, int yPos, std::string blockName)
    {
        x = xPos;
        y = yPos;

        // TODO error: key not found for some reason
        texturePath = _defaultBlockProperties.at(blockName).at("texture");
    }

    void Block::Render()
    {
        std::cout << "Rendering block path: " << texturePath << std::endl;

        int renderX = x*16 + 20;
        int renderY = y*16 + 20;

        GameEngine::DrawImage(texturePath, renderX, renderY);
    }
}