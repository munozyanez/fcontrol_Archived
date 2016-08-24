#include "SystemBlock.h"


SystemBlock::SystemBlock()
{

    std::vector<double> nC,nE,dC,dE;
    nC.clear();
    nE.clear();
    dC.clear();
    dE.clear();
    Initialize(nC,dC,nE,dE);

}

SystemBlock::SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef)
{

    std::vector<double> nE,dE;

    nE.clear();

    dE.clear();


    for (int i=new_numCoef.size(); i<0; i--)
    {
        nE.push_back(i);
    }

    for (int i=new_denCoef.size(); i<0; i--)
    {
        dE.push_back(i);
    }

    Initialize(new_numCoef,new_denCoef,nE,dE);

}


SystemBlock::SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                             const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    Initialize(new_numCoef,new_denCoef,new_numExps,new_denExps);
}

bool SystemBlock::TimeResponse(TimeSignal &input, TimeSignal &output)
{

    //check signal parameters
    if( (input.getFs()!=sFs)|(input.getN()!=sN) )
    {
        SignalParams(input);
        //li::fft_params(input.data, spectral);
        std::cout << "New signal parameters. Storing the new parameters in the block." << std::endl;
    }

    //get the fft from input and save in spectral.
    li::fft(input.data,IN);

    //operate frequencies with transfer function (just rI needed, and first iI value)
    //rI.push_back(iI[0]);

    for (int i=0; i<JW.size(); i++)
    {
        //clear old values
        OUT[i]=C_0;
        //multiply jw by numerators
        for (int j=0; j<numCoef.size(); j++)
        {
            OUT[i]+=numCoef[j];
        }

    }


    //get the ifft from result
    //and store at output
    //discard bad values?


    return true;

}

bool SystemBlock::SignalParams(const TimeSignal &new_signalParams)
{

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

    //compute G based on num, den, and JW
    std::complex<double> numGi, denGi;
    for (int i=0; i<JW.size(); i++)
    {
        //clear old values
        numGi=C_0;
        denGi=C_0;

        //compute numerator
        for (int j=0; j<numCoef.size(); j++)
        {
            numGi += numCoef[j]*pow(JW[i],numExps[j]);
        }

        for (int j=0; j<denCoef.size(); j++)
        {
            numGi += denCoef[j]*pow(JW[i],denExps[j]);
        }

    }

    rI.clear();
    rI.resize(sN/2);
    iI.clear();
    iI.resize(sN/2);
    rO.clear();
    rO.resize(sN/2);
    iO.clear();
    iO.resize(sN/2);

    return true;

}

bool SystemBlock::Initialize(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    numCoef=new_numCoef;
    denCoef=new_denCoef;

    numExps=new_numExps;
    denExps=new_denExps;

    sN=0;

}
