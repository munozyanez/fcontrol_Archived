#include "FPDTuner.h"

FPDTuner::FPDTuner(double new_pm, double new_wcg, double new_dts)
{
    pm=new_pm;
    wcg=new_wcg;
    dts=new_dts;

    //store the iso-m table in memory
    isom = TableInterpolation("lib/fcontrol/phi.m_exp.csv");


}

long FPDTuner::TuneIsom(const SystemBlock & sys, FPDBlock &con)
{

    double alpha, tau_a, k;
    double tgp, tau_x, sahp, cahp;
    double slope, dw=0.1;
    sys.GetMagnitudeAndPhase(dts,wcg,sysmag,sysphi);
    sysphi = sysphi*180/M_PI; //conversion to degrees
    sys.GetMagnitudeAndPhase(dts,wcg+dw,sysmag,slope); //reusing slope
    slope = slope*180/M_PI; //conversion to degrees
    slope = (slope-sysphi) / ( log10(wcg+dw)-log10(wcg) ); //degrees/decade

//    cout << "sysphi="<< sysphi << ", sysmag="<< sysmag << ", slope=" << slope << " (deg)" << endl;

//    cout << "System slope at wcg="<< wcg << ", m=" << slope << "deg/decade" << endl;


    phi=-180+pm-sysphi;

    if (phi >0) //phi positive, derivative.
    {
//        cout << "Searching phi="<< ulong(phi) << ", m=" << ulong(-slope) << "deg/decade" << endl;
        alpha=isom.GetTableValue(ulong(phi),ulong(-slope));
        tgp=tan(phi*M_PI/180);
        sahp = sin(alpha*M_PI/2); //sin of alpha half pi
        cahp = cos(alpha*M_PI/2); //cos of alpha half pi

    }
    else //phi negative, integrator, use derivative table changing phi sign.
    {
//        cout << "Searching phi="<< ulong(-phi) << ", m=" << ulong(-slope) << "deg/decade" << endl;
        alpha=-isom.GetTableValue(ulong(-phi),ulong(-slope));
        tgp=tan(-phi*M_PI/180);
        sahp = sin(-alpha*M_PI/2); //sin of alpha half pi
        cahp = cos(-alpha*M_PI/2); //cos of alpha half pi

    }

    tau_x=1/(tgp/(sahp-tgp*cahp));
    tau_a=1/(tau_x*pow(wcg,alpha));

    //compute k as 1/abs(1+tau_a*jw^alpha)
    k=1/abs(1.0+tau_a*pow(wcg*complex<double>(0,1),alpha) );
    //now divide by plant amplitude
    k=k/sysmag;



//    cout << "alpha: "<< alpha << ", tau_a: "<< tau_a << ", k: "<< k << endl;

    //then change the controller parameters
    con = FPDBlock(k,tau_a*k,alpha,dts);


    return 0;
}



