#ifndef FPDTUNER_H
#define FPDTUNER_H

#include "ToolsFControl.h"

class FPDTuner
{
public:
    FPDTuner();
    FPDTuner(double new_pm, double new_wcg);

private:
    double wcg;     //omega cross gain in radians/second.
    double pm;      //phase margin
    TableInterpolation isom;

//    vector
};

#endif // FPDTUNER_H
