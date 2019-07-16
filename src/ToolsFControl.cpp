#include "ToolsFControl.h"

ToolsFControl::ToolsFControl()
{

}

long ToolsFControl::ToolsFControlInit()
{
//    time(&actualTimeValue);
//    time(&lastTimeValue);
    return 0;
}

long ToolsFControl::SetSamplingTime(double new_dts)
{

    dts= long(new_dts*1000*1000*1000); //dts nanoseconds
    dtsWait = chrono::nanoseconds(dts);

    return 0;
}

double ToolsFControl::WaitSamplingTime()
{
    actualTimeValue = chrono::system_clock::now();

//    time(&actualTimeValue); // here time has been all way around.
//    cout <<std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch(lastTimeValue)).count() << endl;
    tWaited = actualTimeValue.time_since_epoch() - lastTimeValue.time_since_epoch();
//    tWaited = actualTimeValue-lastTimeValue;//chrono::nanoseconds( long(difftime(lastTimeValue,actualTimeValue)*1000*1000) );

    if(dtsWait > tWaited)
    {
        this_thread::sleep_for(dtsWait - tWaited);
    }
    else
    {
        cerr << "dtsWait Exceeded " << endl;
        cout << "dtsWait: " << dec <<dtsWait.count() << ", tWaited: " <<  tWaited.count() << endl;
        cout << "Total time: " << actualTimeValue.time_since_epoch().count() << endl;
    }


    lastTimeValue = chrono::system_clock::now();

    return (dtsWait - tWaited).count()/1000000;
}
