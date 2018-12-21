#include "OnlineSystemIdentification.h"

OnlineSystemIdentification::OnlineSystemIdentification()
{

    ff=0.98;

    P=P.Random();
    phi=phi.setOnes();
    L=L.setZero();
    phi=phi.Random();


}

long OnlineSystemIdentification::UpdateSystem(double input, double output)
{


    //move all phi input data one position backwards to have inputs from actual to last needed past values.
    for (int i=rlms_z-1; i>0; i--) //Leave the first place empty for current input value
    {
        //input indexes can start from zero to include actual input??
        phi(i+rlms_p) = phi(i+rlms_p-1);
    }
    phi(0+rlms_p)=input;

    //        cout << "b0 " << (out[ti]-phi.transpose()*th)/in[ti] << ", at step: " <<  ti << endl;

    //        cout << "phi: " << phi.transpose() << endl;
    L = (P*phi)/(ff+(phi.transpose()*P*phi));
    //        cout << "L " << L << ", at step: " <<  ti << endl;

    P=(1/ff)*(P-L*phi.transpose()*P);
    //        cout << "P " << P << ", at step: " <<  ti << endl;

    err=output-phi.transpose()*th;
    //        cout << "Error preditcion " << err << ", at step: " <<  ti << endl;

    th=th+(L*err);
    cout << "Params " << th.transpose() << endl;

    //move all phi output data one position backwards for the next iteration
    for (int i=rlms_p-1; i>0; i--)
    {
        phi(i) = phi(i-1);
    }
    //and add the actual value
    phi(0)=output;

    return 0;

}
