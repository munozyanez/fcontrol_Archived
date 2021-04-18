#include "Block.h"

BaseBlock::BaseBlock()
{
    saturation=false;
    maxOut = 0;
    minOut = 0;
}


long BaseBlock::SetSaturation(double low, double high)
{
    saturation=true;
    maxOut = high;
    minOut = low;

    return 0;
}



