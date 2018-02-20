#include "SystemBlock.h"

#include <math.h>       /* isnormal */

SystemBlock::SystemBlock()
{


//    std::vector<double> nC = {1};
//    std::vector<double> nE = {0};
//    std::vector<double> dC = {1};
//    std::vector<double> dE = {0};
//    InitSystemBlock(nC,dC,nE,dE);

}

SystemBlock::SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef)
{

    std::vector<double> nE,dE;

    nE.clear();

    dE.clear();


    for (int i=0; i<new_numCoef.size(); i++)
    {
        nE.push_back(i);
    }

    for (int i=0; i<new_denCoef.size(); i++)
    {
        dE.push_back(i);
    }


    InitSystemBlock(new_numCoef,new_denCoef,nE,dE);

}

SystemBlock::SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, double new_gain)
{
    std::vector<double> nE(1,new_numCoef.size()),dE(1,new_denCoef.size());
    InitSystemBlock(new_numCoef, new_denCoef,nE,dE);
    if (this->gain!=1)
    {
        std::cerr << "Gain was not unit in transfer function. It was: " << gain << std::endl;
    }
    gain *= new_gain;
    std::cout << "New gain: " << gain << std::endl;
}


SystemBlock::SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                             const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    InitSystemBlock(new_numCoef,new_denCoef,new_numExps,new_denExps);
}

SystemBlock::SystemBlock(const TransferFunction &newH)
{

    InitSystemBlock(newH.getNumCoef(), newH.getDenCoef(), newH.getNumExps(), newH.getDenExps());
}



SystemBlock::SystemBlock(double b0, double b1, double a0, double a1)
{
    std::vector<double> num(2,0);
    std::vector<double> den(2,0);

    den[0] = a0;
    den[1] = a1;
    num[0] = b0;
    num[1] = b1;

    std::vector<double> nE(2,1),dE(2,1);

    InitSystemBlock(num,den,nE,dE);

}

double SystemBlock::GetNumOrder() const
{
    return numCoef.size();

}

double SystemBlock::GetDenOrder() const
{
    return denCoef.size();

}

long SystemBlock::GetTransfer(std::vector<double> &numCoefficients, std::vector<double> &denCoefficients) const
{
    numCoefficients = numCoef;
    denCoefficients = denCoef;

}

double SystemBlock::GetState()
{
    return state;

}


double SystemBlock::OutputUpdate(double new_input)
{
    double response=0;
    //check signal parameters

    //apply only to updated value (new_value). As an update, older values are known.
    //start from 1, due to old first value will drop from new.

    //int N=numCoef.size();
    oldInputs.erase(oldInputs.begin());
    //now add the last value
    oldInputs.push_back(new_input);

    for (int i=0; i<oldInputs.size(); i++)
    {
        response += numCoef[i]*oldInputs[i];
    }
    //apply gain (only numerator)
    response = response*gain;
    //N=denCoef.size();//use all outputs but actual (at the end of vector)
    //std::cout<<"BROKE "<< (int(oldStates.size())-1) <<""<<std::endl;
    for (int i=0; i<int(oldStates.size()); i++)
    {
        response -= denCoef[i]*oldStates[i];
    }

    //apply saturation
    if (maxOut!=0)
    {
        response = std::min(response,maxOut);
    }
    //apply saturation
    if (minOut!=0)
    {
        response = std::max(response,minOut);
    }
    //now add the last value
    oldStates.push_back(response);
    //delete first value
    oldStates.erase(oldStates.begin());

    state = response;

    return response;
}

//SystemBlock SystemBlock::operator*(const SystemBlock & sys)
//{
//    std::vector<double> numResult(numCoef.size()-1+sys.GetNumOrder()-1);
//    std::vector<double> denResult(denCoef.size()-1+sys.GetDenOrder()-1);

//    std::vector<double> numSys,denSys;
//    sys.GetTransfer(numSys, denSys);

//    std::cout << "[UNDER CONSTRUCTION!!]]" << std::endl;


//}



//SystemBlock& SystemBlock::operator >> (SystemBlock &output)
//{
//    output.OutputUpdate(GetState());
//    return output;

//}

//SystemBlock& SystemBlock::operator <<=(double &input)
//{
//    OutputUpdate(input);
//    return *this;

//}

//SystemBlock &SystemBlock::operator <<(SystemBlock &input)
//{

//    OutputUpdate(input.GetState());
//    std::cout  << state << "..." << input.GetState() << std::endl;

//    return *this;
//}

long SystemBlock::Reset()
{
    for (int i=0; i<oldStates.size(); i++)
    {
        oldStates[i]=0;
    }

    for (int i=0; i<oldInputs.size(); i++)
    {
        oldInputs[i]=0;
    }
    state=0;
}

long SystemBlock::Reset(double new_state)
{
    for (int i=0; i<oldStates.size(); i++)
    {
        oldStates[i]=new_state;
    }

    for (int i=0; i<oldInputs.size(); i++)
    {
        oldInputs[i]=0;
    }
    state=new_state;
}

bool SystemBlock::InitSystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{

    numCoef=new_numCoef;
    denCoef=new_denCoef;

    //normalize for denominator highest exponent coefficient = 1
    //all functions will behave like it.
    double numGain = numCoef.back();


    if (numGain == 0)
    {
        //find the first coeff not 0
        for (long i=numCoef.size()-1; i>=0; i--)
        {

            if(numCoef[i]!=0)
            {
                //found
                numGain = numCoef[i];
                break;
            }

        }
    }

    double denGain = denCoef.back();

    if (denGain == 0)
    {
        //find the first coeff not 0
        for (long i=denCoef.size()-1; i>=0; i--)
        {
            if(denCoef[i]!=0)
            {
                //found
                denGain = denCoef[i];
                break;
            }

        }
    }

    gain = numGain/denGain;

    //if gain is not a number something fishy is going on
    //probably denGain=0
    if(!std::isnormal(gain))
    {

        std::cout << "Block gain error " << gain << std::endl;
        std::cout << "Check Denominator " << std::endl;


    }
    std::cout << "Block gain: " << gain << std::endl;
    std::cout << "numCoef : [";
    if (numGain !=0)
    {
        for (int i=0; i<new_numCoef.size();i++)
        {
            numCoef[i]=new_numCoef[i]/numGain;
            std::cout << numCoef[i] << "," ;
        }
    }
    std::cout << "]" << std::endl;

    std::cout << "denCoef : [";
    for (int i=0; i<new_denCoef.size();i++)
    {
        denCoef[i]=new_denCoef[i]/denGain;
        std::cout << denCoef[i] << "," ;

    }
    std::cout << "]" << std::endl;


    numExps=new_numExps;
    denExps=new_denExps;

    maxOut = 0;
    minOut = 0;

    oldStates.clear();
    for(int i=0;i<denCoef.size()-1;i++)
    {
        oldStates.push_back(0.0);
    }
    oldInputs.clear();
    for(int i=0;i<numCoef.size();i++)
    {
        oldInputs.push_back(0.0);
    }
    state = 0;


}

std::vector<double> SystemBlock::PolynomialProduct(std::vector<double> p, std::vector<double> q)
{

    //long newdeg = p.size()-1 + q.size()-1; // degree of p*q

    // Special case for a polynomial of size 0
    if (p.size() == 0 or q.size() == 0)
    {
        return std::vector<double>(0);
    }

    std::vector<double> r(p.size()-1 + q.size()-1);

    for (int i = 0; i < p.size(); ++i)
    {
        for (int j = 0; j < q.size(); ++j)
        {
            r[i + j] = r[i + j] + p[i]*q[j];
        }
    }

    return r;

}
