#include "FPDTuner.h"

FPDTuner::FPDTuner() : FPDTuner( 60, 1)
{

}

FPDTuner::FPDTuner(double new_pm = 60, double new_wcg = 1)
{
    pm=new_pm;
    wcg=new_wcg;

    //store the iso-m table in memory
    isom = TableInterpolation("phi.m_exp.csv");


}

long FPDTuner::Tune(double new_phi, double new_gain)
{


}

