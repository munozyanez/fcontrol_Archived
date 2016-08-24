#include "libinterface.h"

fftw_complex * a;

std::complex<double> * b;
std_complex c;
double * signalAddress=NULL;
int signalSize=0;


bool li::fft(std::vector<double> &signal, std::vector<std_complex> &spectral)
{
    static fftw_plan fft_d;


    //call library and return signals
    if ( (signalAddress!=signal.data()) | (signalSize!=signal.size()) )
    {
        fft_d=fftw_plan_dft_r2c_1d(signal.size(),
                                        signal.data(), //real amplitude vector
                                        reinterpret_cast<fftw_complex*>(spectral.data()), //complex frequency vector
                                        FFTW_PRESERVE_INPUT);

    }


    fftw_execute(fft_d);


    return true;

}

bool li::ifft(std::vector<std_complex> &spectral, std::vector<double> &signal)
{
    //call library and return signals

    static fftw_plan fft_i;


    //call library and return signals
    if ( (signalAddress!=signal.data()) | (signalSize!=signal.size()) )
    {
        fft_i=fftw_plan_dft_c2r_1d(signal.size(),
                                   reinterpret_cast<fftw_complex*>(spectral.data()), //complex frequency vector
                                   signal.data(), //real amplitude vector
                                   FFTW_PRESERVE_INPUT);

    }


    fftw_execute(fft_i);


    return true;


}

bool li::fft_params(const std::vector<double> &signal_sample, std::vector<std::complex<double> > &spectral_sample)
{

}
