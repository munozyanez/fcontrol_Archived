#ifndef LIBINTERFACE_H
#define LIBINTERFACE_H

#include <vector>

//if you #include <complex.h> before <fftw3.h>, then fftw_complex is defined to be the native complex type (std::complex)
//and you can manipulate it with ordinary arithmetic (e.g. x = y * (3+4*I) (http://www.fftw.org/fftw3_doc/Complex-numbers.html#Complex-numbers);
#include <complex>
#include <fftw3.h>

namespace li
{

//fftw lib
bool fft(const std::vector<double> &signal, std::vector<double> &fReal, std::vector<double> &fImag);
bool ifft(const std::vector<double> &fReal,const std::vector<double> &fImag, std::vector<double> &signal);

//maths lib
bool complex_pow(double realC, double imagC, double power);

}// end namespace li

#endif // LIBINTERFACE_H
