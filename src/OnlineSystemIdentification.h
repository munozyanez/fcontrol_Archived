#ifndef ONLINESYSTEMIDENTIFICATION_H
#define ONLINESYSTEMIDENTIFICATION_H


#define rlms_z (1)                //Number of input past values including current input
#define rlms_p 2					//Number of output past values
//#define rlms_N (rlms_z+rlms_p)      //phi dimension
#define rlms_N (32)      //phi dimension More order than that will throw assertion on eigen

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
    OnlineSystemIdentification(long new_numOrder, long new_denOrder, double new_ff = 0.98);
    long UpdateSystem(double input, double output);
    long GetZTransferFunction(vector<double>& num,vector<double>& den);
    vector<double> GetParamsVector();

private:

    long numOrder,denOrder, order;

//    Matrix<double,Dynamic,Dynamic> P;
//    Matrix<double,Dynamic,1> phi;
//    Matrix<double,Dynamic,1> L;
//    Matrix<double,Dynamic,1> th;

//    Matrix<double, 1, 1, 0, 1, 1> ff; //forgetting factor
    double ff;
    Matrix<double, Dynamic, Dynamic, 0, rlms_N, rlms_N> P; //max order rlms_N #defined
    Matrix<double, Dynamic, 1, 0, rlms_N, 1> phi; //max order rlms_N
    Matrix<double, Dynamic, 1, 0, rlms_N, 1>  L;//max order rlms_N
    Matrix<double, Dynamic, 1, 0, rlms_N, 1> th;//max order rlms_N

    double err;
    double ti; //time index

    vector<double> oldOuts, oldIns;

};

#endif // ONLINESYSTEMIDENTIFICATION_H
