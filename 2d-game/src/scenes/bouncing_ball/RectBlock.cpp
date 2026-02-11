#include "RectBlock.h"

void RectBlock::render(Graphics* g)
{
    g->FillRect(x, y, width, height, RED);
}