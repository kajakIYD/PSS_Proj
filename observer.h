#ifndef OBSERVER_H
#define OBSERVER_H
#include <QVector>

/*!
 * \brief simulate_step
 * perform one simulation step
 * double input -
 */
class Observer {
public:
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    virtual ~Observer () {}
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    virtual void Update(double x, double y) = 0;
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    virtual void Update(double y) = 0;
};

#endif // OBSERVER_H
