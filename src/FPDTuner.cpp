#include "FPDTuner.h"

FPDTuner::FPDTuner(double new_pm, double new_wcg, double new_dts)
{
    pm=new_pm;
    wcg=new_wcg;
    dts=new_dts;

    //store the iso-m table in memory
    isom = TableInterpolation("phi.m_exp.csv");


}

long FPDTuner::TuneIsom(const SystemBlock & sys, FPDBlock &con)
{



    return 0;
}



