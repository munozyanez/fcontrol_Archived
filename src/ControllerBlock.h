#ifndef CONTROLLERBLOCK_H
#define CONTROLLERBLOCK_H

#include "SystemBlock.h"
#include "TimeSignal.h"

class ControllerBlock : public SystemBlock
{
public:
    ControllerBlock();
    ControllerBlock(TimeSignal new_signal);

    double ControlSignal(double new_error);


private:

    TimeSignal error;
    bool InitControllerBlock(TimeSignal init_signal);


};

#endif // CONTROLLERBLOCK_H
