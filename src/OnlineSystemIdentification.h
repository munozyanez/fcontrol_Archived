#ifndef ONLINESYSTEMIDENTIFICATION_H
#define ONLINESYSTEMIDENTIFICATION_H


#define rlms_z (1)                //Number of input past values including current input
#define rlms_p 2					//Number of output past values
#define rlms_N (rlms_z+rlms_p)      //phi dimension

#include <vector>
#undef Success //as in http://eigen.tuxfamily.org/bz/show_bug.cgi?id=253
#include <Eigen/Dense>
#define Success 0 //as in http://eigen.tuxfamily.org/bz/show_bug.cgi?id=253
#include <iostream>

using namespace std;
using namespace Eigen;



class OnlineSystemIdentification
{
public:
    OnlineSystemIdentification();
    long UpdateSystem(double input, double output);

    OnlineSystemIdentification(double new_ff);
private:

    double ff; //forgetting factor

    Matrix<double,rlms_N,rlms_N> P;
    Matrix<double,rlms_N,1> phi;
    Matrix<double,rlms_N,1> L;
    Matrix<double,rlms_N,1> th;
    double err;

    vector<double> oldOuts, oldIns;

};

#endif // ONLINESYSTEMIDENTIFICATION_H
