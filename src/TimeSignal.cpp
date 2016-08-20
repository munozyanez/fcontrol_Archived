#include "TimeSignal.h"

TimeSignal::TimeSignal()
{
    //default signal is 256 points sampled at 1 Hz
    Initialize(256,1);
}

TimeSignal::TimeSignal(double init_fs, unsigned int init_size)
{
    Initialize(init_fs,init_size);
}

bool TimeSignal::Initialize(unsigned int new_size, double new_fs)
{
    fs=new_fs;
    dts=1/fs;
    N=new_size;
    data.clear();
    data.resize(N);

    return true;

}

bool TimeSignal::GetParams(unsigned int &out_size, double &out_fs) const
{
    out_fs = fs;
    out_size = N;

}

double TimeSignal::getFs() const
{
    return fs;
}

double TimeSignal::getN() const
{
    return N;
}

double TimeSignal::getDts() const
{
    return dts;
}

