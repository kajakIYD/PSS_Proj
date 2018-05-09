#ifndef GPC_H
#define GPC_H
#include "regulator.h"
#include <vector>
#include <deque>

class GPC : public Regulator
{
public:
    /*!
     * \brief Constructor that construct regulator PID with specified gain(kr),
     * Integration time(Ti), derivative time, filtering parameter N, weight coefficient b,
     * upper (max_u) and lower (min_u) bound of control signal and
     * signal generator (generator) that helps to generate SetPoint signal
     */
    GPC(double H, double L, double alpha, double max_u, double min_u, Generator *generator);
    /*!
     * \brief Destructor
     */
    ~GPC();

    /*!
     * \brief Method updating plots
     */
    void Update(double y1, double y2, double y3){}
    void Update(double x, double y){}
    void Update(double y);
    /*!
     * \brief simulate_step
     * perform one simulation step
     * give an output depending on input
     */
    double Simulate_step(double input);
    /*!
     * \brief Simple getter for regulation control (double u)
     */
    double GetU();
    /*!
     * \brief Simple getter for regulation setPoint
     */
    double GetSP();
    /*!
     * \brief Setter for Simulation time for regulator (in case of resetting simulation)
     */
    void SetTime(int time);

private:
    double s_H;
    double s_L;
    double s_alpha;
    std::vector<double> s_controlVector; //Series of L-long new controls
    std::vector<double> s_referenceTrajectory; //Series of H-long reference trajectory vector

};

#endif // GPC_H
