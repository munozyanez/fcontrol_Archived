#include "PIDBlock.h"

PIDBlock::PIDBlock()
{


}

PIDBlock::PIDBlock(double kp, double ki, double kd, double Ts)
{

    iBlock = SystemBlock(
                ki*Ts/2,   ki*Ts/2,
                -1,        1);
//    dBlock = SystemBlock(
//                kd*-1,  kd*1,
//                0,      Ts*1);
    // LPF implementation
    double N = 20;    // LPFfilter N
    dBlock = SystemBlock(
                kd*-1*N ,   kd*1*N,
                -1      ,   1+N*Ts*1);

    pBlock = kp;

}

double PIDBlock::UpdateControl(double input)
{
    double cp,ci,cd,c;

    cp=input*pBlock;
    ci = iBlock.OutputUpdate(input);
    cd = dBlock.OutputUpdate(input);
    c=cp+ci+cd;
    if (signbit(state)==signbit(c))
    {
        state=c;
    }
    else
    {
        iBlock.Reset();
        ci = iBlock.OutputUpdate(input);
        c=cp+ci+cd;
        state=c;

    }

//    std::cout << "pid : " << cp << ","<< ci << ","<< cd << std::endl;
//    std::cout << "pid : " <<state << std::endl;

    return state;

}

double PIDBlock::OutputUpdate(double input)
{

    return UpdateControl(input);
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
