#ifndef PIDBLOCK_H
#define PIDBLOCK_H

#include "fcontrol.h"


class PIDBlock
{
public:
    PIDBlock();
    PIDBlock(double kp, double ki, double kd, double Ts);
    double UpdateControl(double input);

private:
    SystemBlock iBlock;
    SystemBlock dBlock;
    double pBlock;
};

#endif // PIDBLOCK_H
