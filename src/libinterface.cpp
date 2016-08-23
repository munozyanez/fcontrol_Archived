#include "libinterface.h"

fftw_complex * a;
std::complex<double> * b;
std_complex c;

bool li::fft(const std::vector<double> &signal, std::vector<std_complex> &spectral)
{
    //TODO call library and return signals correct

    a=reinterpret_cast<fftw_complex*>(b);


}

bool li::ifft(const std::vector<double> &fReal,const std::vector<double> &fImag, std::vector<double> &signal)
{
    //TODO call library and return signals correct
    signal=fReal;


}

bool li::fft_params(const std::vector<double> &signal_sample, std::vector<std::complex<double> > &spectral_sample)
{

}
