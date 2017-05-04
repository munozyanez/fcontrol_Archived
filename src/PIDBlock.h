#ifndef PIDBLOCK_H
#define PIDBLOCK_H

#include "fcontrol.h"


class PIDBlock
{
public:
    PIDBlock();
    PIDBlock(double kp, double ki, double kd, double Ts);
    double UpdateControl(double input);

    double OutputUpdate(double input);

//    void operator>>(double & output);
//    void operator>>(SystemBlock & output);

    double GetState() const;

private:
    SystemBlock iBlock;
    SystemBlock dBlock;
    double pBlock;
    double state;
    SystemBlock pidBlock;
};

#endif // PIDBLOCK_H
