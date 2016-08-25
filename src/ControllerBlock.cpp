#include "ControllerBlock.h"

ControllerBlock::ControllerBlock()
{

}

ControllerBlock::ControllerBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef)
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


    Initialize(new_numCoef,new_denCoef,nE,dE);
}

ControllerBlock::ControllerBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    Initialize(new_numCoef,new_denCoef,new_numExps,new_denExps);

}

bool ControllerBlock::Initialize(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    numCoef=new_numCoef;
    denCoef=new_denCoef;

    numExps=new_numExps;
    denExps=new_denExps;


    return true;
}


bool ControllerBlock::SignalParams(const TimeSignal &new_signalParams)
{
/*
    new_signalParams.GetParams(sN, sFs);
    sDts = 1/sFs;
    jwN=((sN/2)+1);

    JW.clear();
    JW.resize( (sN/2)+1 );
    for(int i=0; i<JW.size(); i++)
    {
        JW[i]=2*M_PI*(i*sFs)*C_I;

    }

    IN.clear();
    IN.resize(jwN);

    OUT.clear();
    OUT.resize(jwN);

    G.clear();
    G.resize(jwN);

    //compute G based on num, den, and JW
    std::complex<double> numGi, denGi;

    //TODO: deal with constant value JW[0]=0 , and division by 0.
    G[0]=1;
    for (int i=1; i<JW.size(); i++)
    {
        //clear old values
        numGi=C_0;
        denGi=C_0;

        //compute numerator
        for (int j=0; j<numCoef.size(); j++)
        {
            numGi += numCoef[j]*pow(JW[i],numExps[j]);

        }
        //compute denominator
        for (int j=0; j<denCoef.size(); j++)
        {
            denGi += denCoef[j]*pow(JW[i],denExps[j]);

        }
        G[i]=numGi/denGi;
        //std::cout << G[i] << " at " << i << std::endl;

    }

    rI.clear();
    rI.resize(sN/2);
    iI.clear();
    iI.resize(sN/2);
    rO.clear();
    rO.resize(sN/2);
    iO.clear();
    iO.resize(sN/2);
*/
    return true;

}

