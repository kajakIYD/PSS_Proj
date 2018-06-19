#ifndef SIGNAL_H
#define SIGNAL_H
#include <cmath>
#include <QVector>

class Signal
{
public:
    /*!
     * \brief Constrctor
     */
    Signal();
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    virtual double simulate (int t) = 0;
};

#endif // SIGNAL_H
