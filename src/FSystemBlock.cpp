#include "FSystemBlock.h"

FSystemBlock::FSystemBlock()
{

    sN=0;

}

FSystemBlock::FSystemBlock(const TimeSignal &timeImpulseResponse)
{

//    g.clear();
//    for (int i=0; i<timeImpulseResponse.data.size(); i++)
//    {
//        g.push_back(timeImpulseResponse.data[i]);
//        std::cout << "i : " << i << ",g[i] : " << g[i] << std::endl;
//    }
//    std::cout << std::endl;
    g=timeImpulseResponse.data;

}

long FSystemBlock::FSystemBlockInit()
{

}


bool FSystemBlock::TimeResponse(TimeSignal &input, TimeSignal &output)
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

double FSystemBlock::TimeResponseUpdate(const TimeSignal &old_input, const double &new_value)
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

double FSystemBlock::OutputUpdate(double new_input)
{
    double response=0;


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
    //delete first value
    //TODO: Check complexity for shift
    //maybe deque is better for that operation
    oldStates[0]=response;
    oldStates = oldStates.cshift(1);
    //now add the last value
    state = response;

    return response;
}



bool FSystemBlock::SignalParams(const TimeSignal &new_signalParams)
{

    new_signalParams.GetParams(sN, sFs);
    sDts = 1/sFs;
    jwN=((sN/2)+1);

    JW.resize(0);
    JW.resize( (sN/2)+1 );
    for(int i=0; i<JW.size(); i++)
    {
        JW[i]=2*M_PI*(i*sFs)*C_I;

    }

    IN.resize(0);
    IN.resize(jwN);

    OUT.resize(0);
    OUT.resize(jwN);

    G.resize(0);
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

//        //compute numerator
//        for (int j=0; j<numCoef.size(); j++)
//        {
//            numGi += numCoef[j]*pow(JW[i],numExps[j]);

//        }
//        //compute denominator
//        for (int j=0; j<denCoef.size(); j++)
//        {
//            denGi += denCoef[j]*pow(JW[i],denExps[j]);

//        }
        G[i]=numGi/denGi;
        //std::cout << G[i] << " at " << i << std::endl;

    }

    //compute g based on G
    g.resize(0);
    g.resize(sN);
    li::ifft(G,g);

    rI.resize(0);
    rI.resize(sN/2);
    iI.resize(0);
    iI.resize(sN/2);
    rO.resize(0);
    rO.resize(sN/2);
    iO.resize(0);
    iO.resize(sN/2);

    return true;

}

