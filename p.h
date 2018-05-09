#ifndef P_H
#define P_H
#include "regulator.h"

class P : public Regulator
{
public:
    /*!
     * \brief Constructor that construct object with specified gain(kr) and
     * signal generator (generator)
     */
    P(double kr, Generator *generator);
    /*!
     * \brief Constructor
     */
    P(){}
    /*!
     * \brief Destructor
     */
    ~P();
    void Update(double x, double y, double z){}
    void Update(double x, double y){}
    void Update(double y);
    //    void SetSP(double SP);

    /*!
     * \brief simulate_step
     * perform one simulation step
     * give an output depending on input
     */
    double Simulate_step(double input);

    void SetTime(int time){}
    /*!
     * \brief Simple getter for regulation control (double u)
     */
    double GetU();

    double GetSP();

    /*!
     * \brief Simulation time for regulator
     */
    int time=0;
private:
    double kr;
    double SP;
    double u;
};

#endif // P_H
