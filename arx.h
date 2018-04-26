#ifndef ARX_H
#define ARX_H

#include <deque>
#include <vector>
#include <random>

#include "siso.h"
#include "subject.h"
#include "config.h"

class ARX : public SISO, public Subject
{
public:
    ARX();
    ~ARX();

    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    double Simulate_step(double input);
    /*!
     * \brief GetSwitchTime()
     * Used for getting time of parameter switching
     */
    int GetSwitchTime();
    /*!
     * \brief UpdateParameters();
     * Used for updating parameters of arx object during simulation
     */
    void UpdateParameters();

    /*!
     * \brief UpdateParameters();
     * Used for reseting parameters of arx object during simulation
     */
    void ResetParameters();

    /*!
     * \brief public_U
     * Current control value, depending on value from GUI
     * make it private and add method that allow to set that value
     */
    double public_U=0;

private:

    Config *conf;
    std::default_random_engine generator;
    std::vector<double> parA;
    std::vector<double> parB;
    std::deque<double> u;
    std::deque<double> y;

    int s_dA;
    int s_dB;
    int s_k;
    int s_time = 0;
    int s_switchTime=0;
    double s_var = 0.00000001;

};

#endif // ARX_H
