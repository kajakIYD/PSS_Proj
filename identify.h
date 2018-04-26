#ifndef IDENTIFY_H
#define IDENTIFY_H

using namespace std;

class Identify
{
public:
    ///Set initial contidion for P matrix
    Identify();

    ///Parameters vector<double> u -  known control
    /// vector<double> y - analised object output
    ///Return Vector of vectors "P"
    double Calculate_P(double u, double y);



private:
    double s_beta = 1000;
    double s_lambda = 0.99;
    //Vector of doubles a, size = dA;
    //Vector of doubles b, size = dB

    //Vector of doubles phi size k+dB+dA

    //Vector of vectors P with initial condition set in constructor
    double P;
};

#endif // IDENTIFY_H
