#ifndef FSYSTEMBLOCK_H
#define FSYSTEMBLOCK_H

#include <complex>
#define C_I std::complex<double>(0,1)
#define C_0 std::complex<double>(0,0)

#include "TimeSignal.h"

class FSystemBlock : public Block
{
public:
    FSystemBlock();
    FSystemBlock(const TimeSignal &timeImpulseResponse);

    bool TimeResponse(TimeSignal &input, TimeSignal &output);
    double TimeResponseUpdate(const TimeSignal &old_input, const double &new_value);
    double OutputUpdate(const TimeSignal &old_input, const double &new_value);


private:
    long FSystemBlockInit();
    std::vector< std::complex<double> > IN,OUT; //spectral values of input and output.

    std::vector<double> rI,iI;//frecuency values of input (real and imag).
    std::vector<double> rO,iO;//frecuency values of output (real and imag).
    std::vector< std::complex<double> > JW;//jw are imaginary numbers.
    std::vector< std::complex<double> > G;//Processed Gain spectral values. Frequency block transference function.
    std::vector<double> g;//Processed gain time values. Time block transference function.

    //signal parameters
    double sFs,sDts;
    unsigned int sN, jwN;
};

#endif // FSYSTEMBLOCK_H
