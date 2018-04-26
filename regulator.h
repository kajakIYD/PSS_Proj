#ifndef REGULATOR_H
#define REGULATOR_H
#include "observer.h"
#include "subject.h"
#include "siso.h"
#include "generator.h"
#include <random>

//Obiekt powinien powiadamiać zarówno plota jak i obiekt
class Regulator : public SISO, public Observer
{

public:
    /*!
     * \brief Constructor
     */
    Regulator();
    /*!
     * \brief Virtual destructor
     */
    virtual ~Regulator () {}
    /*!
     * \brief simulate_step
     * perform one simulation step
     * give an output depending on input
     */
    virtual void Update(double u, double y)=0;
    virtual void Update(double y)=0;
    virtual double Simulate_step(double input)=0;
    virtual void SetTime(int time)=0;
    /*!
     * \brief Simple getter for regulation setpoint (double SP)
     */
    virtual double GetSP()=0;

    double max_u;
    double min_u;

protected:
    Generator *s_generator;
    int s_time;
    double u;
    double e;

};

#endif // REGULATOR_H
