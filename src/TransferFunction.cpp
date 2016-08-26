#include "TransferFunction.h"

TransferFunction::TransferFunction()
{

    std::vector<double> nC,nE,dC,dE;
    nC.clear();
    nE.clear();
    dC.clear();
    dE.clear();
    InitTransferFunction(nC,dC,nE,dE);

}

TransferFunction::TransferFunction(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef)
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


    InitTransferFunction(new_numCoef,new_denCoef,nE,dE);

}


TransferFunction::TransferFunction(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                             const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    InitTransferFunction(new_numCoef,new_denCoef,new_numExps,new_denExps);
}

TransferFunction::TransferFunction(int numSize, int denSize, double num[], double den[])
{

}


bool TransferFunction::InitTransferFunction(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    if ( (new_numCoef.size()!=new_numExps.size())|(new_denCoef.size()!=new_denExps.size()) )
    {
        std::cout << "Wrong transfer function parameters" << std::endl;
        return false;
    }
    numCoef=new_numCoef;
    denCoef=new_denCoef;

    numExps=new_numExps;
    denExps=new_denExps;

    return true;

}
