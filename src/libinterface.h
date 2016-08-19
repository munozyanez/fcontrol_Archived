#ifndef LIBINTERFACE_H
#define LIBINTERFACE_H

#include <vector>

namespace li
{

//fftw lib
bool fft(const std::vector<double> &signal, std::vector<double> &fReal, std::vector<double> &fImag);
bool ifft(const std::vector<double> &fReal,const std::vector<double> &fImag, std::vector<double> &signal);

//maths lib
bool complex_pow(double realC, double imagC, double power);

}// end namespace li

#endif // LIBINTERFACE_H
