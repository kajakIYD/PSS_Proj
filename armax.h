#ifndef ARMAX_H
#define ARMAX_H

#include <deque>
#include <vector>
#include <random>

#include "siso.h"
#include "subject.h"
#include "config.h"

class ARMAX : public SISO, public Subject
{
public:
    ARMAX();
    ~ARMAX();

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
     * \brief GetSwitchPeriod
     * \return switch period:p
     */
    int GetSwitchPeriod();

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
     * \brief Getter used for acquireing C vector
     */
    std::vector<double> GetC();


    /*!
     * \brief Getter used for acquireing A degree
     */
    int GetAdegree();

    /*!
     * \brief Getter used for acquireing B degree
     */
    int GetBdegree();

    /*!
     * \brief Getter used for acquireing B degree
     */
    int GetCdegree();

    /*!
     * \brief Getter used for acquireing k parameter
     */
    int Getk();

    /*!
     * \brief Getter used for acquireing Y vector
     */
    std::deque<double> GetY();

    /*!
     * \brief Getter used for acquireing part of Y vector used in output calculation
     */
    std::deque<double> GetNewestY();

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
    std::vector<double> s_parC;
    std::vector<double> s_changes_parA;
    std::vector<double> s_changes_parB;
    std::vector<double> s_changes_parC;
    std::deque<double> u;
    std::deque<double> y;
    std::deque<double> yFromBeginning;
    std::deque<double> e;

    int s_dA;
    int s_dB;
    int s_dC;
    int s_k;
    int s_time = 0;
    int s_switchTime=0;
    int s_switchTimePeriod = 0;
    double s_var = 0.00000001;

    void CalculateParamChanges();
};


#endif // ARMAX_H
