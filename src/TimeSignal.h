#ifndef TIMESIGNAL_H
#define TIMESIGNAL_H

#include <vector>

class TimeSignal
{
public:
    TimeSignal();
    TimeSignal(unsigned int init_size, double init_fs);

    bool Initialize(unsigned int new_size, double new_fs);
    bool GetParams(unsigned int &out_size, double &out_fs) const;

    //variables exposed
    //data must be exposed for better performance.
    //Think of this class as an improved std::vector.
    std::vector<double> data;

    double getFs() const;

    double getN() const;


    double getDts() const;

private:
    double fs;//frequency of sampling
    double dts;//time of sampling
    unsigned int N;//number of data

};

#endif // TIMESIGNAL_H
