#ifndef PARTIALDERIVATIVE_H
#define PARTIALDERIVATIVE_H

#define PARTIALDERIVATIVE_MAXSIZE 100

#include<valarray>
#include <stdio.h>      //cout
#include <math.h>       //tgamma

using namespace std;

class PartialDerivative
{
public:
    PartialDerivative();
    PartialDerivative(double new_exp, double new_dts);
private:
    long Init(double new_exp, double new_dts);

    double exp;
    double dts;
    valarray<double> fir;

};

#endif // PARTIALDERIVATIVE_H
