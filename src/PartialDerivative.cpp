#include "PartialDerivative.h"

PartialDerivative::PartialDerivative()
{

    Init(0.01,1);
}


PartialDerivative::PartialDerivative(double new_exp, double new_dts)
{

    Init(new_exp,new_dts);
}




long PartialDerivative::Init(double new_exp, double new_dts)
{

    dts=new_dts;
    exp=new_exp;

    double bi=0;

    fir.resize(0);
    for (int i=0; i<PARTIALDERIVATIVE_MAXSIZE; i++)
    {
        bi = tgamma(exp+1) / (tgamma(i+1)*tgamma(exp-i+1));
        //implement here gl discrete
        //printf ("tgamma(%f) = %f\n", param, result );

    }

    return 0;
}
