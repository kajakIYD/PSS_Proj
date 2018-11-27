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


    virtual void Identify_step(std::vector<double> args) = 0;
    /*!
     * \brief Get_param
     * Getter function to get identify parameters
     * double input -
     */
    virtual deque<vector<double>> Get_param() = 0;

    virtual ~IdentifyUber() {}
};

#endif // IDENTIFYUBER_H
