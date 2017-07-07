#include "libinterface.h"

fftw_complex * a;

std::complex<double> * b;
complex_std c;
double * signalAddress=NULL;
int signalSize=0;
complex_std * spectralAddress=NULL;
int spectralSize=0;


bool li::fft(std::vector<double> &signal, std::vector<complex_std> &spectral)
{
    static fftw_plan fft_d;



    //call library and return signals
    if ( (signalAddress!=signal.data()) | (signalSize!=signal.size()) )
    {
        std::cout << "New signal. Updating plan." << std::endl;

        //save signal as next plan function will empty the vector
        std::vector<double> signalSave(signal);
        fft_d=fftw_plan_dft_r2c_1d(signal.size(),
                                        signal.data(), //real amplitude vector
                                        reinterpret_cast<fftw_complex*>(spectral.data()), //complex frequency vector
                                        FFTW_PRESERVE_INPUT);

        //now restore the signal. Remember not to change vector address.
        for (int i=0; i<signal.size(); i++)
        {

            signal[i]=signalSave[i];
            //std::cout << signal[i];

        }
    }


    fftw_execute(fft_d);


    return true;

}

bool li::ifft(std::vector<complex_std> &spectral, std::vector<double> &signal)
{
    //call library and return signals

    static fftw_plan fft_i;


    //call library and return signals
    if ( (spectralAddress!=spectral.data()) | (spectralSize!=spectral.size()) )
    {
        std::cout << "New spectral. Updating plan." << std::endl;

        //save spectral as next plan function will empty the vector
        std::vector<complex_std> spectralSave(spectral);

        fft_i=fftw_plan_dft_c2r_1d(signal.size(),
                                   reinterpret_cast<fftw_complex*>(spectral.data()), //complex frequency vector
                                   signal.data(), //real amplitude vector
                                   FFTW_PRESERVE_INPUT);
        //now restore the signal. Remember not to change vector address.
        for (int i=0; i<spectral.size(); i++)
        {

            spectral[i]=spectralSave[i];
            //std::cout << spectral[i];

        }
    }


    fftw_execute(fft_i);

    // rescale
    for (int i=0; i<signal.size(); i++)
    {

        signal[i]=signal[i]/signal.size();

    }

    return true;


}

bool li::fft_params(const std::vector<double> &signal_sample, std::vector<std::complex<double> > &spectral_sample)
{

}
