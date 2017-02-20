#include "PIDBlock.h"

PIDBlock::PIDBlock()
{


}

PIDBlock::PIDBlock(double kp, double ki, double kd, double Ts)
{

    iBlock = SystemBlock(ki*0,ki*Ts*1,-1,1);
    dBlock = SystemBlock(kd*-1,kd*1,0,Ts*1);
    pBlock = kp;

}

double PIDBlock::UpdateControl(double input)
{
    double cp,ci,cd;

    cp=input*pBlock;
    ci = iBlock.OutputUpdate(input);
    cd = dBlock.OutputUpdate(input);
    //std::cout << "pid : " << cp << ","<< ci << ","<< cd << std::endl;
    return cp+ci+cd;

}