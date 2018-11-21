#ifndef IDENTIFYARMAX_H
#define IDENTIFYARMAX_H

#include "identifyuber.h"

#include <cmath>
#include <deque>
#include <vector>
#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class IdentifyARMAX : public IdentifyUber
{
public:
    IdentifyARMAX(int dA, int dB, int dC, int k);
    ~IdentifyARMAX();
    /*!
     * \brief Identification_step
     * perform one Identification step
     * double input -
     */
    void Identify_step(double u, double y);
    /*!
     * \brief Get_param
     * Getter function to get identify parameters
     * double input -
     */
    deque<double> Get_param();
    /*!
     * \brief Get_A
     * Getter function to get A polynomial
     */
    std::vector<double> Get_A();
    /*!
     * \brief Get_B
     * Getter function to get B polynomial
     */
    std::vector<double> Get_B();
    /*!
     * \brief Get_B
     * Getter function to get B polynomial
     */
   std::vector<double> Get_C();

private:

    void Identify_initialization();

    deque<double> u, y, e_dashed;
    std::vector<double> A, B, C;

    int s_dA;
    int s_dB;
    int s_dC;
    int s_k;

    double lambda = 1;          // ze wzoru 32.8
    double lambda_zap = 0.98;   // dla metody zapominania
    double beta;
    double eps;

    // Wektor nieznanych parametrów obiektu
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

#endif // IDENTIFYARMAX_H
