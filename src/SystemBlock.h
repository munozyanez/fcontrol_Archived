#ifndef SYSTEMBLOCK_H
#define SYSTEMBLOCK_H

#include <vector>
#include <math.h>
#include <iostream>

#include "libinterface.h"
#include "TimeSignal.h"


/**
 * @brief The SystemBlock class:
 * This class encapsulates a system control block, defined by its transference function G.
 * Library uses fourier transform, so the function must be a quotient of fourier transforms.
 */


class SystemBlock
{
public:
    SystemBlock();
    SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef);
    SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                const std::vector<double> &new_numExps, const std::vector<double> &new_denExps);

    bool TimeResponse(const TimeSignal &input, TimeSignal &output);


private:
    //transference function G
    std::vector<double> numCoef,denCoef;//numerator and denominator coefficients
    std::vector<double> numExps,denExps;//numerator and denominator jw powers

    std::vector<double> rI,iI;//frecuency values of input (real and imag)
    std::vector<double> rO,iO;//frecuency values of output (real and imag)
    std::vector<double> jw;//jw are imaginary part only numbers. If jw[i]=b means b*j.

    //signal parameters
    double sFs,sDts;
    unsigned int sN, jwN;

    bool SignalParams(const TimeSignal &new_signalParams);

    bool Initialize(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
            const std::vector<double> &new_numExps, const std::vector<double> &new_denExps);


};

#endif // SYSTEMBLOCK_H
