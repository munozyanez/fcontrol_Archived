#ifndef CONTROLLERBLOCK_H
#define CONTROLLERBLOCK_H

#include "SystemBlock.h"
#include "TimeSignal.h"
#include "TransferFunction.h"

class ControllerBlock : public SystemBlock
{
public:
    ControllerBlock();
    ControllerBlock(TransferFunction new_transfer);
    ControllerBlock(TransferFunction new_transfer, TimeSignal new_signal);

    double ControlSignal(double new_error);


private:

    TimeSignal errorSignal;
    //TransferFunction transfer;
    bool InitControllerBlock(TimeSignal init_signal);


};

#endif // CONTROLLERBLOCK_H
