#ifndef IDENTIFY_H
#define IDENTIFY_H
#include <vector>

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
    double s_q;
    double s_r;
    double s_lambda_min;
    double s_lambda_max;

    //Ilosc pomiarow
    int N;
    //Vector of doubles a, size = dA;
    std::vector<double> a ={};
    //Vector of doubles b, size = dB
    std::vector<double> b ={};

    //Vector of doubles phi size k+dB+dA
    std::vector<double> phi ={};

    //Vector of vectors P with initial condition set in constructor
    std::vector<std::vector<double>> s_P ={};
    //Biblioteka
};

#endif // IDENTIFY_H
