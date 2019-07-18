#ifndef FPDTUNER_H
#define FPDTUNER_H


class FPDTuner
{
public:
    FPDTuner(double new_pm, double new_wcg);

private:
    double wcg;     //omega cross gain in radians/second.
    double pm;      //phase margin

//    vector
};

#endif // FPDTUNER_H
