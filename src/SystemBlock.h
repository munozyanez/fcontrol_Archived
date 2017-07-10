#ifndef SYSTEMBLOCK_H
#define SYSTEMBLOCK_H





#include "TransferFunction.h"
#include "Block.h"


/**
 * @brief The SystemBlock class:
 * This class encapsulates a system control block, defined by its transference function G.
 * .
 */


class SystemBlock : public Block
{
public:
    SystemBlock();
    SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef);
    SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, double new_gain);
    SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                const std::vector<double> &new_numExps, const std::vector<double> &new_denExps);
    SystemBlock(const TransferFunction &newH);
    SystemBlock(double b0,double b1,double a0,double a1);

    double GetNumOrder() const;
    double GetDenOrder() const;
    long GetTransfer(std::vector<double> & numCoefficients, std::vector<double> & denCoefficients) const;
    virtual double GetState();


    double OutputUpdate(double new_input);


//    SystemBlock operator*(const SystemBlock & sys);
//    //SystemBlock& operator>>=(double & output);
//    SystemBlock& operator>>(SystemBlock & output);

//    SystemBlock& operator <<= (double& input);
//    SystemBlock& operator << (SystemBlock& input);


    long Reset();

//    friend double& operator , (double input, double& output)
//    {
//        output=input;
//        return output;
//    }

private:
    //transfer function G
    double gain; //the gain for the transfer function.
    std::vector<double> numCoef,denCoef;//numerator and denominator coefficients.
    std::vector<double> numExps,denExps;//numerator and denominator jw powers.


    //bool SignalParams(const TimeSignal &new_signalParams);

    bool InitSystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
            const std::vector<double> &new_numExps, const std::vector<double> &new_denExps);
    std::vector<double> PolynomialProduct(std::vector<double> p, std::vector<double> q);

    //state values
    double state;
    std::vector<double> oldStates;
    std::vector<double> oldInputs;





};

//SystemBlock & operator>>( SystemBlock &system, double output)
//{
//    return system;

//}

//SystemBlock& operator>>(double input, SystemBlock &system)
//{
//    system.OutputUpdate(input);
//    return system;

//}


#endif // SYSTEMBLOCK_H
