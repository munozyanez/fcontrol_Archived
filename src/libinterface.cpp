#include "libinterface.h"

fftw_complex * a;
fftw_plan fft_params;

std::complex<double> * b;
std_complex c;
double * signalAddress=NULL;
int signalSize=0;

bool li::fft(std::vector<double> &signal, std::vector<std_complex> &spectral)
{
    //TODO call library and return signals correct
    if ( (signalAddress!=signal.data()) | (signalSize!=signal.size()) )
    {
        /*fftw_plan_dft_r2c_1d(signal.size(),
                             signal.data(),
                             reinterpret_cast<fftw_complex*>(spectral.data()),
                             FFTW_PRESERVE_INPUT);
*/
    }


    a=reinterpret_cast<fftw_complex*>(b);

    return true;

}

bool li::ifft(std::vector<std_complex> &spectral, std::vector<double> &signal)
{
    //TODO call library and return signals correct


}

bool li::fft_params(const std::vector<double> &signal_sample, std::vector<std::complex<double> > &spectral_sample)
{

}
