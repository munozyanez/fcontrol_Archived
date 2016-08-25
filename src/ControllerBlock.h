#ifndef CONTROLLERBLOCK_H
#define CONTROLLERBLOCK_H

#include <vector>
#include <math.h>
#include <iostream>
#include <complex>
#define C_I std::complex<double>(0,1)
#define C_0 std::complex<double>(0,0)


#include "libinterface.h"
#include "TimeSignal.h"

#define gSIZE 100
#define GSIZE (gSIZE/2)+1


class ControllerBlock
{
public:
    ControllerBlock();
    ControllerBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef);
    ControllerBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                const std::vector<double> &new_numExps, const std::vector<double> &new_denExps);


private:

    //transference function G
    std::vector<double> numCoef,denCoef;//numerator and denominator coefficients
    std::vector<double> numExps,denExps;//numerator and denominator jw powers

    std::vector< std::complex<double> > JW;//jw are imaginary numbers.
    std::vector< std::complex<double> > G;//Processed Gain spectral values.

    bool Initialize(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                    const std::vector<double> &new_numExps, const std::vector<double> &new_denExps);
    bool SignalParams(const TimeSignal &new_signalParams);
};

#endif // CONTROLLERBLOCK_H
