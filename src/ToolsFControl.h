#ifndef TOOLSFCONTROL_H
#define TOOLSFCONTROL_H

#include <chrono>
#include <thread>
#include <iostream>

using namespace std;
class ToolsFControl
{
public:
    ToolsFControl();
    long ToolsFControlInit();
    long SetSamplingTime(double new_dts);
    long WaitSamplingTime();

private:
    chrono::system_clock::time_point actualTimeValue, lastTimeValue; //last time value
//    long timeAlreadyWaited; //in nanoseconds
    long dts; //sampling time nanoseconds.
    chrono::nanoseconds dtsWait, tWaited;
    chrono::system_clock clock;

};

#endif // TOOLSFCONTROL_H
