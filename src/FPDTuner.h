#ifndef FPDTUNER_H
#define FPDTUNER_H

#include "ToolsFControl.h"
#include "SystemBlock.h"
#include "FPDBlock.h"

class FPDTuner
{
public:
    FPDTuner(double new_pm = 60, double new_wcg = 1, double new_dts = 0.01);

    long TuneIsom(const SystemBlock &sys, FPDBlock &con);

private:


    double wcg;     //desired omega cross gain in radians/second.
    double pm;      //desired phase margin

    double sysmag;  //system magnitude at wcg
    double sysphi;  //system phase at wcg

    double sysPhi;  //system phase in radians
    double sysGain; //system at wgc
    TableInterpolation isom;

    double dts;



//    vector
};

#endif // FPDTUNER_H
