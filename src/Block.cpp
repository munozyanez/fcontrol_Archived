#include "Block.h"

Block::Block()
{

}


long Block::SetSaturation(double low, double high)
{
    maxOut = high;
    minOut = low;

}



