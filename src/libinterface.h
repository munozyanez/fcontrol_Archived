#ifndef LIBINTERFACE_H
#define LIBINTERFACE_H

#include <vector>

//if you #include <complex.h> before <fftw3.h>, then fftw_complex is defined to be the native complex type (std::complex)
//and you can manipulate it with ordinary arithmetic (e.g. x = y * (3+4*I) (http://www.fftw.org/fftw3_doc/Complex-numbers.html#Complex-numbers);
#include <complex>
#include <fftw3.h>

#define std_complex std::complex<double>

namespace li
{

//fftw lib
bool fft_params(const std::vector<double> &signal_sample, std::vector<std_complex > &spectral_sample);
bool fft(const std::vector<double> &signal, std::vector<std_complex > &spectral);
bool ifft(const std::vector<double> &fReal,const std::vector<double> &fImag, std::vector<double> &signal);


}// end namespace li

#endif // LIBINTERFACE_H
