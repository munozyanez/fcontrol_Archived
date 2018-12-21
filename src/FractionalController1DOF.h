#ifndef FRACTIONALCONTROLLER1DOF_H
#define FRACTIONALCONTROLLER1DOF_H

#include "SystemBlock.h"
#include "FractionalDerivative.h"


class FractionalController1DOF
{
public:
    FractionalController1DOF();
    FractionalController1DOF(double new_exp, double new_dts);

private:
    long Init(double new_exp, double new_dts);
    SystemBlock ipart;
    FractionalDerivative fpart;

    double iexp;
    double exp;
    double dts;

};

#endif // FRACTIONALCONTROLLER1DOF_H
