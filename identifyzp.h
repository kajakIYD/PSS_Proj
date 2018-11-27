#ifndef IDENTIFYZP_H
#define IDENTIFYZP_H

#include "identifyuber.h"

#include <vector>
#include <deque>
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class IdentifyZP : public IdentifyUber
{
public:
    IdentifyZP(int s_dR, int s_dS, int s_dT, int s_k);
    /*!
     * \brief Identification_step
     * perform one Identification step
     * double input -
     */
    void Identify_step(std::vector<double> args) override;
    std::deque<std::vector<double>> Get_param() override;

private:
    void Identify_initialization();

    deque<double> u, y, w;
    std::vector<double> R, S, T;

    int s_dR;
    int s_dS;
    int s_dT;
    int s_k;

    double lambda = 1;          // ze wzoru 32.8
    double lambda_zap = 0.98;   // dla metody zapominania
    double beta;
    double eps;
    double gamma;

    // Wektor nieznanych parametrów R,S,T
    MatrixXd theta;
    // Macierz kowariancji
    MatrixXd p;
    // Macierz reprezentująca współczynniki zapominania
    MatrixXd diag;
    // Wektor wzmocnienia
    MatrixXd k;
    // Phi - Algorytm WRNMK
    MatrixXd phi;
};

#endif // IDENTIFYZP_H
