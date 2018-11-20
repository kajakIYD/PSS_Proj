#ifndef IDENTIFYUBER_H
#define IDENTIFYUBER_H

#include <cmath>
#include <deque>
#include <vector>
#include <iostream>
#include <Eigen/Dense>


using namespace Eigen;
using namespace std;


class IdentifyUber
{
public:
    IdentifyUber();
    virtual ~IdentifyUber() {};

    virtual void Identify_step(double u, double y) = 0;
    /*!
     * \brief Get_param
     * Getter function to get identify parameters
     * double input -
     */
    virtual deque<double> Get_param() = 0;
    /*!
     * \brief Get_A
     * Getter function to get A polynomial
     */
    virtual std::vector<double> Get_A() = 0;
    /*!
     * \brief Get_B
     * Getter function to get B polynomial
     */
    virtual std::vector<double> Get_B() = 0;
    /*!
     * \brief Get_B
     * Getter function to get B polynomial
     */
   virtual std::vector<double> Get_C() = 0;

};

#endif // IDENTIFYUBER_H
