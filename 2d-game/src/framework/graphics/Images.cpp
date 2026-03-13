#include "Images.h"

namespace GameEngine
{
    void DrawImage(std::string imageName, int x, int y, GameImageRenderOptions options = {})
    {
        // TODO: Implement image scaling (nearest neighbor)

        GameImage *img = GetImage(imageName);
        unsigned char *imgPx = img->getPixels();

        int xOffset = 0, yOffset = 0, xMult = 1, yMult = 1;
        if (options.flipHorizontal)
        {
            xOffset += img->getWidth() - 1;
            xMult = -1;
        }
        if (options.flipVertical)
        {
            yOffset += img->getHeight() - 1;
            yMult = -1;
        }

        for (int imgX = 0; imgX < img->getWidth(); imgX++)
        {
            for (int imgY = 0; imgY < img->getHeight(); imgY++)
            {
                int imgIndex = (imgY * img->getWidth() + imgX) * 4;
                if (imgPx[imgIndex + 3] != 0)
                {
                    int drawX = x + imgX * xMult + xOffset;
                    int drawY = y + imgY * yMult + yOffset;
                    if (IsOnScreen(drawX, drawY))
                    {
                        FillVoxel(drawX, drawY, imgPx[imgIndex], imgPx[imgIndex + 1], imgPx[imgIndex + 2], imgPx[imgIndex + 3]);
                    }
                }
            }
        }
    }
}