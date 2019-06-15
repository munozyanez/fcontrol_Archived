#include "OnlineSystemIdentification.h"

OnlineSystemIdentification::OnlineSystemIdentification() : OnlineSystemIdentification(1,1,0.98)
{

    //Default params: order 1, forgetting factor 0.98


}

OnlineSystemIdentification::OnlineSystemIdentification(long new_numOrder, long new_denOrder, double new_ff)
{
    ff=new_ff;

    denOrder= new_denOrder;
    numOrder= new_numOrder;

    if(denOrder < numOrder)
    {
        numOrder = denOrder;
        cout << "Only causal systems!!! Reducing numerator to order: " << numOrder << endl;
    } //now it is causal, numOrder <= denOrder

    //share orders available, allowing den use numerator unused orders.
    if( denOrder + numOrder > rlms_N)
    {
        if (numOrder < rlms_N/2) //Give num orders to den.
        {
            denOrder = rlms_N - numOrder;
            cout << "Maximum order reached. Reducing orders to: num = " << numOrder << ", den =" << denOrder << endl;
        }
        else //The only possibility is to reduce both to maximum size.
        {
            numOrder = rlms_N/2;
            denOrder = numOrder;
            cout << "Maximum order reached. Reducing orders to: num = " << numOrder << ", den = " << denOrder << endl;


        }
    }

    order = numOrder+1 + denOrder; //+1 include numerator actual input
    phiNumIndex = denOrder+1-1;//num next to den +1 and starts at zero -1.
    phiLastIndex = order-1; //starts at zero -1.

//    //    P.resize(order,NoChange); //no longer needed
//    P=P.Random(order,order);
//    cout << "--> Initial P <--" << endl << P << endl;
//    //    phi.resize(order,order); //no longer needed
//    phi=phi.Random(order,1);
//    cout << "--> Initial phi <--" << endl << phi << endl;
//    //    L.resize(order,NoChange);//no longer needed
//    L=L.setZero(order,1);
//    cout << "--> Initial L <--" << endl << L  << endl;

//    th=th.setZero(order,1);
//    cout << "--> Initial th <--" << endl << th << endl << "--------------order : " << numOrder << " / " << denOrder << endl;

    //    P.resize(order,NoChange); //no longer needed
    R=R.Random(order,order);
    cout << "--> Initial R <--" << endl << R << endl;
    //    phi.resize(order,order); //no longer needed
    phi=phi.Random(order,1);
    cout << "--> Initial phi <--" << endl << phi << endl;
    //    L.resize(order,NoChange);//no longer needed
    L=L.setZero(order,1);
    cout << "--> Initial L <--" << endl << L  << endl;

    th=th.setZero(order,1);
    cout << "--> Initial th <--" << endl << th << endl << "--------------order : " << numOrder << " / " << denOrder << endl;



}

//double OnlineSystemIdentification::UpdateSystem(double input, double output)
//{

//    ti++;
//    //move all phi input data one position backwards to have inputs from actual to last needed past values.
//    for (int i=numOrder-1; i>0; i--) //Leave the first place empty for current input value
//    {
//        //input indexes can start from zero to include actual input??
//        phi[i+denOrder] = phi[i+denOrder-1];
//    }
//    phi(0+denOrder)=input;

//    //        cout << "b0 " << (out[ti]-phi.transpose()*th)/in[ti] << ", at step: " <<  ti << endl;
//    //        cout << "phi: " << phi.transpose() << endl;

//    L = (P*phi)/(ff+(phi.transpose()*P*phi));
//    //    cout << "L " << L.transpose() << ", at step: " <<  ti << endl;

//    P=(1/ff)*(P-L*phi.transpose()*P);
//    //    cout << "P " << P << ", at step: " <<  ti << endl;

//    err=output-phi.transpose()*th;
//    //    cout << "Error preditcion " << err << ", at step: " <<  ti << endl;

//    th=th+(L*err);
//    //    cout << "Params " << th.transpose() << endl;

//    //move all phi output data one position backwards for the next iteration
//    for (int i=denOrder-1; i>0; i--)
//    {
//        phi[i] = phi[i-1];
//    }
//    //and add the actual value
//    phi(0)=output;
//    return err;

//}

double OnlineSystemIdentification::UpdateSystem(double input, double output)
{

    ti++;
    //move all phi input data one position backwards to have inputs from actual to last needed past values.
    for (int i=phiLastIndex; i>phiNumIndex; i--) //order-1 is full phi size
    {
        //input indexes can start from zero to include actual input??
       // cout << "phiLastIndex: " << phiLastIndex << " ; phiNumIndex: " << phiNumIndex << endl;
        phi[i] = phi[i-1];
    }
    phi(phiNumIndex)=input;

//            cout << "b0 " << (output[ti]-phi.transpose()*th)/input[ti] << ", at step: " <<  ti << endl;
//    cout << "phi: " << phi.transpose() << endl;



    R = ff*R + phi*phi.transpose();
//    cout << "R: " << R << endl;

    th = th + R.inverse()*phi*(output - phi.transpose()*th);
//    cout << "th: " << th.transpose() << endl;

//    cout << "phi: " << phi.transpose() << endl;
//    cout << "test: phiT*theta " << phi.transpose()*th << endl;


    //move all phi output data one position backwards for next iteration
    for (int i=denOrder-1; i>0; i--)
    {
        phi[i] = phi[i-1];
    }
    //and add the actual value
    phi(0)=-output;

    return err;

}

double OnlineSystemIdentification::GetZTransferFunction(vector<double> &num, vector<double> &den)
{

//    for (int i=0; i<numOrder; i++)
//    {
//        num[i]=th[i];
//        //        cout << "num i= " << i << " num: " << num[i] << " th: " << th(i)<<endl;
//    }

//    for (int i=0; i<denOrder; i++)
//    {
//        den[i]=th[i+numOrder];
//        //        cout << "den i= " << i << " den: " << den[i] << " th: " << th(i+numOrder)<<endl;
//    }
//    return err;
    cout << "th: " << th.transpose() << endl;

    num[0]=th[phiLastIndex];
    cout << "G=tf([ "  ;
    for (int i=1; i<=phiNumIndex; i++)
    {
        num[i]=th[phiLastIndex-i];
        cout << num[i]<< ", " ;
    }
    cout  << num[0] << "],[ ";


    for (int i=0; i<phiNumIndex; i++)
    {
        den[i]=th[phiNumIndex-1-i];
        cout << den[i]<< ", " ;

    }
    cout << 1 << "], ";
    den[phiNumIndex]=1;
    cout  << ")"<< endl;

    return err;

}


double OnlineSystemIdentification::PrintZTransferFunction(double dts)
{

    //todo: scilab format
//    cout << "G=tf([ " << th[0] ;
//    for (int i=1; i<numOrder; i++)
//    {
//        cout << ", " << th[i];
//    }
//    cout << "],[ "<< th[numOrder];
//    for (int i=1; i<denOrder; i++)
//    {
//        cout << ", " << th[i+numOrder];

//    }
//    cout << "]," <<dts<< ")"<< endl;

    cout << "G=tf([ " << th[phiNumIndex] ;
    for (int i=phiNumIndex+1; i<=phiLastIndex; i++)
    {
        cout << ", " << th[i];
    }
    cout << "],[ " << 1;
    for (int i=0; i<phiNumIndex; i++)
    {
        cout << ", " << th[i];

    }
    cout << "]," <<dts<< ")"<< endl;

    return err;

}


double OnlineSystemIdentification::PrintParamsVector()
{
    cout << "Parameters vector: [";
    for (int i=0; i<order; i++)
    {
        cout << th[i] << ", ";
    }
    cout << "]" << endl;
    return err;
}

vector<double> OnlineSystemIdentification::GetParamsVector()
{
    vector<double> params(order);
    for (int i=0; i<order; i++)
    {
        params[i]=th(i);
    }
    return params;
}
