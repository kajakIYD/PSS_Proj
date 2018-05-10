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
     * \brief Used for reseting parameters of arx object during simulation
     */
    void ResetParameters();

    /*!
     * \brief Getter used for acuiring A vector
     */
    std::vector<double> GetA();

    /*!
     * \brief Getter used for acquireing B vector
     */
    std::vector<double> GetB();

    /*!
     * \brief Getter used for acquireing Y vector
     */
    std::deque<double> GetY();

    /*!
     * \brief Getter used for acquireing U vector
     */
    std::deque<double> GetU();

    /*!
     * \brief Setter used for acquireing U vector
     */
    void SetY(std::deque<double> yNew);

    /*!
     * \brief Setter used for acquireing U vector
     */
    void SetU(std::deque<double> uNew);

    /*!
     * \brief public_U
     * Current control value, depending on value from GUI
     * make it private and add method that allow to set that value
     */
    double public_U=0;


private:

    Config *conf;
    std::default_random_engine generator;
    std::vector<double> s_parA;
    std::vector<double> s_parB;
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
