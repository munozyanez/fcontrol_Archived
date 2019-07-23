#ifndef FPDTUNER_H
#define FPDTUNER_H

#include "ToolsFControl.h"

class FPDTuner
{
public:
    FPDTuner();
    FPDTuner(double new_pm, double new_wcg);

    long Tune(double new_phi, double new_gain);

private:
    double wcg;     //omega cross gain in radians/second.
    double pm;      //phase margin

    double sysPhi;  //system phase in radians
    double sysGain; //system at wgc
    TableInterpolation isom;

//    vector
};

#endif // FPDTUNER_H
