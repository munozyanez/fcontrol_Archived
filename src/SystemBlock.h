#ifndef SYSTEMBLOCK_H
#define SYSTEMBLOCK_H

#include <vector>
#include <math.h>
#include <iostream>
#include <complex>
#define C_I std::complex<double>(0,1)
#define C_0 std::complex<double>(0,0)


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

    bool TimeResponse(TimeSignal &input, TimeSignal &output);
    double TimeResponseUpdate(const TimeSignal &old_input, const double &new_value);


private:
    //transference function G
    std::vector<double> numCoef,denCoef;//numerator and denominator coefficients
    std::vector<double> numExps,denExps;//numerator and denominator jw powers

    std::vector< std::complex<double> > IN,OUT; //spectral values of input and output

    std::vector<double> rI,iI;//frecuency values of input (real and imag)
    std::vector<double> rO,iO;//frecuency values of output (real and imag)
    std::vector< std::complex<double> > JW;//jw are imaginary numbers.
    std::vector< std::complex<double> > G;//Processed Gain spectral values. Frequency block transference function.
    std::vector<double> g;//Processed gain time values. Time block transference function.

    //signal parameters
    double sFs,sDts;
    unsigned int sN, jwN;

    bool SignalParams(const TimeSignal &new_signalParams);

    bool InitSystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
            const std::vector<double> &new_numExps, const std::vector<double> &new_denExps);


};

#endif // SYSTEMBLOCK_H
