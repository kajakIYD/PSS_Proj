#ifndef PID_H
#define PID_H
#include "regulator.h"


class PID : public Regulator
{
public:
    /*!
     * \brief Constructor that construct object with specified gain(kr) and
     * signal generator (generator)
     */
    PID(double kr, double Ti, double Td, double N, double b, double max_u, double min_u, Generator *generator);
    /*!
     * \brief Constructor
     */
    PID();
    /*!
     * \brief Destructor
     */
    ~PID();
    void Update(double x, double y){}
    void Update(double y);
    //    void SetSP(double SP);

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


    void SetTime(int time);

    /*!
     * \brief Simulation time for regulator
     */
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
