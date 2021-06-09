#ifndef FRACTIONALDERIVATIVE_H
#define FRACTIONALDERIVATIVE_H

#define FRACTIONALDERIVATIVE_MAXSIZE 1024

#include<valarray>
#include <iostream>      //cout
#include <math.h>       //tgamma
#include <vector>       //vector
#include "Block.h"
#include "Fraccional.h"

using namespace std;

class FractionalDerivative : public BaseBlock
{
public:
    FractionalDerivative();
    FractionalDerivative(double new_exp, double new_dts);
    double OutputUpdate(double new_input);
    double GetState() const;

    vector<double> GetVfir() const;

private:
    long Init(double new_exp, double new_dts);
    double exp;

    double dts;
    double firtol;
    valarray<double> fir;
    vector<double> vfir;
    long N;
    std::valarray<double> convolution_n;

    //state values
    double state;
    std::valarray<double> oldStates;
    std::valarray<double> oldInputs;

    clConv conv1;
    float cv1[FRACTIONALDERIVATIVE_MAXSIZE],cv2[FRACTIONALDERIVATIVE_MAXSIZE];



};

#endif // FRACTIONALDERIVATIVE_H
