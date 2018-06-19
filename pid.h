#ifndef PID_H
#define PID_H
#include "regulator.h"


class PID : public Regulator
{
public:
    /*!
     * \brief Constructor that construct regulator PID with specified gain(kr),
     * Integration time(Ti), derivative time, filtering parameter N, weight coefficient b,
     * upper (max_u) and lower (min_u) bound of control signal and
     * signal generator (generator) that helps to generate SetPoint signal
     */
    PID(double kr, double Ti, double Td, double N, double b, double max_u, double min_u, Generator *generator);
    PID(){}
    /*!
     * \brief Destructor
     */
    ~PID();

    /*!
     * \brief Method updating plots
     */
    void Update(double y1, double y2, double y3){
        (void) y1;
        (void) y2;
        (void) y3;
    }
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
    double kr;
    double Ti;
    double Td;
    double Tp=1;
    double N;
    double b;
    double SP;
    double u_p;
    double u_i;
    double prev_u_i=0;
    double Fi=0;
    double u_d;
    double prev_u_d=0;
    double u;
    double prev_y=0;
};

#endif // PID_H
