#include "PIDBlock.h"

PIDBlock::PIDBlock()
{


}

PIDBlock::PIDBlock(double kp, double ki, double kd, double Ts)
{

    iBlock = SystemBlock(ki*0,ki*Ts*1,-1,1);
    //dBlock = SystemBlock(kd*-1,kd*1,0,Ts*1);
    // LPF implementation
    double N = 20;    // LPFfilter N
    dBlock = SystemBlock(kd*-1*N,kd*1*N,-1,1+N*Ts*1);

    pBlock = kp;

}

double PIDBlock::UpdateControl(double input)
{
    double cp,ci,cd;

    cp=input*pBlock;
    ci = iBlock.OutputUpdate(input);
    cd = dBlock.OutputUpdate(input);
    //std::cout << "pid : " << cp << ","<< ci << ","<< cd << std::endl;
    state=cp+ci+cd;
    return state;
    std::cout << "pid : " <<state << std::endl;

}

double PIDBlock::OutputUpdate(double input)
{

    UpdateControl(input);
}

double PIDBlock::GetState() const
{
    return state;
}

//void PIDBlock::operator>>(double &output)
//{
//    output = state;

//}

//void PIDBlock::operator>>(SystemBlock &output)
//{
//    output.OutputUpdate(state);

//}
