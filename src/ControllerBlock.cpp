#include "ControllerBlock.h"

ControllerBlock::ControllerBlock()
{
    TimeSignal default_signal; //default signal is 256 data, all zeros

    InitControllerBlock(default_signal);
    //default Transfer is G=1

    //InitSystemBlock();

}

ControllerBlock::ControllerBlock(TimeSignal new_signal)
{
    InitControllerBlock(new_signal);


}

double ControllerBlock::ControlSignal(double new_error)
{

    return 0;
}

bool ControllerBlock::InitControllerBlock(TimeSignal init_signal)
{
    error = init_signal;


    return true;
}



