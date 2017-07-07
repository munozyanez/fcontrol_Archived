#ifndef BLOCK_H
#define BLOCK_H


#include <vector>
#include <deque>
#include <valarray>
#include <math.h>
#include <iostream>

class Block
{
public:
    Block();

    friend double operator > (double input, Block& output)
    {
        return output.OutputUpdate(input);
    }
private:

    double saturation;

    virtual double OutputUpdate(double new_input)=0;




};

#endif // BLOCK_H
