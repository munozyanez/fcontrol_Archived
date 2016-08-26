#ifndef TRANSFERFUNCTION_H
#define TRANSFERFUNCTION_H


class TransferFunction
{
public:
    TransferFunction();


private:

    //transference function G
    //numerator and denominator coefficients and exponents
    //vector is ordered
    std::vector<double> numerator,denominator;



    std::vector< std::complex<double> > G;//Processed Gain spectral values. Frequency block transference function.
    std::vector<double> g;//Processed gain time values. Time block transference function.

    //private functions

    InitTransferFunction(const std::vector<double> &new_num, const std::vector<double> &new_den );

};

#endif // TRANSFERFUNCTION_H
