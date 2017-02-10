#include "SystemBlock.h"


SystemBlock::SystemBlock()
{


    std::vector<double> nC = {1};
    std::vector<double> nE = {0};
    std::vector<double> dC = {1};
    std::vector<double> dE = {0};
    InitSystemBlock(nC,dC,nE,dE);

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


SystemBlock::SystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef,
                             const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{
    InitSystemBlock(new_numCoef,new_denCoef,new_numExps,new_denExps);
}

SystemBlock::SystemBlock(const TransferFunction &newH)
{

    InitSystemBlock(newH.getNumCoef(), newH.getDenCoef(), newH.getNumExps(), newH.getDenExps());
}

SystemBlock::SystemBlock(const TimeSignal &timeImpulseResponse)
{

    g.clear();
    for (int i=0; i<timeImpulseResponse.data.size(); i++)
    {
        g.push_back(timeImpulseResponse.data[i]);
        std::cout << "i : " << i << ",g[i] : " << g[i] << std::endl;
    }
    std::cout << std::endl;

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

    for (int i=0; i<input.getN(); i++)
    {

        //std::cout << input.data[i];

    }
    //get the fft from input and save at IN.
    li::fft(input.data,IN);


    //operate IN with transfer function G
    for (int i=0; i<JW.size(); i++)
    {
        OUT[i]=IN[i]*G[i];
        //std::cout << IN[i] << " from IN at " << i << std::endl;
        //std::cout << OUT[i] << " from OUT at " << i << std::endl;

    }


    //get the ifft from result
    li::ifft(OUT, output.data);
    //and store at output
    //discard bad values?


    return true;

}

double SystemBlock::TimeResponseUpdate(const TimeSignal &old_input, const double &new_value)
{
    double response=0;
    //check signal parameters
    if( (old_input.getFs()!=sFs)|(old_input.getN()!=sN) )
    {
        SignalParams(old_input);
        //li::fft_params(input.data, spectral);
        std::cout << "New signal parameters. Storing the new parameters in the block." << std::endl;
    }

    //apply convolution only to updated value (new_value). As an update, older values are known.
    //start from 1, due to old first value will drop from new convolution.
    for (int i=1; i<sN; i++)
    {
        response += g[sN-i]*old_input.data[i];
        std::cout << "i = " << i<< " ,sN-i:" << sN-i  << " ,g[sN-i]:" << g[sN-i] << " ,old_input.data[i]:"<< old_input.data[i] << std::endl;
    }
    //now add the last value
    response += g[0]*new_value;

    return response;
}

double SystemBlock::OutputUpdate(const TimeSignal &old_input, const double &new_value)
{
    double response=0;
    //check signal parameters

    //apply only to updated value (new_value). As an update, older values are known.
    //start from 1, due to old first value will drop from new.

    //int N=numCoef.size();


    for (int i=1; i<numCoef.size(); i++)
    {
        response += numCoef[i]*old_input.data[i-1];
    }
    response += numCoef[0]*new_value;
    //N=denCoef.size();
    for (int i=1; i<denCoef.size(); i++)
    {
        response -= denCoef[i]*old_input.data[i-1];
    }
    //response=response/numCoef.back();
    //delete first value
    oldStates.erase(oldStates.begin());
    //now add the last value
    oldStates.push_back(response);

    return response;
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

    for (int i=0; i<numCoef.size(); i++)
    {
        response += numCoef[i]*oldInputs[i];
    }

    //N=denCoef.size();
    for (int i=1; i<denCoef.size(); i++)
    {
        response -= denCoef[i]*oldStates[i];
    }
    //response=response/numCoef.back();
    //delete first value
    oldStates.erase(oldStates.begin());
    //now add the last value
    oldStates.push_back(response);

    return response;
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

    //compute g based on G
    g.clear();
    g.resize(sN);
    li::ifft(G,g);

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

bool SystemBlock::InitSystemBlock(const std::vector<double> &new_numCoef, const std::vector<double> &new_denCoef, const std::vector<double> &new_numExps, const std::vector<double> &new_denExps)
{

    numCoef=new_numCoef;
    denCoef=new_denCoef;

    //normalize for denominator highest exponent coefficient = 1
    //all functions will behave like it.
    double divisor = denCoef.back();
    std::cout << "normalizing Block with: " << divisor << std::endl;
    std::cout << "numCoef : [";
    for (int i=0; i<new_numCoef.size();i++)
    {
        numCoef[i]=new_numCoef[i]/divisor;
        std::cout << numCoef[i] << "," ;
    }
    std::cout << "]" << std::endl;

    std::cout << "denCoef : [";
    for (int i=0; i<new_denCoef.size();i++)
    {
        denCoef[i]=new_denCoef[i]/divisor;
        std::cout << denCoef[i] << "," ;

    }
    std::cout << "]" << std::endl;


    numExps=new_numExps;
    denExps=new_denExps;

    sN=0;

    oldStates.clear();
    for(int i=0;i<denCoef.size();i++)
    {
        oldStates.push_back(0.0);
    }
    oldInputs.clear();
    for(int i=0;i<denCoef.size();i++)
    {
        oldInputs.push_back(0.0);
    }


}
