#include "TextureAnimation.h"

namespace GameEngine
{
    void TextureAnimation::UpdateAnimation(float dt)
    {
        if (animActive)
        {
            lastAnimUpdate += dt;
            if (lastAnimUpdate > animDelaySecs)
            {
                animFrame++;
                if (animFrame >= animFrames.size())
                    animFrame = 0;
                lastAnimUpdate = 0;
            }
        }
        else
        {
            animFrame = 0;
        }
    }
}