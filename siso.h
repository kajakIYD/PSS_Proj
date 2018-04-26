
#ifndef SISO_H
#define SISO_H

/*!
 * \brief simulate_step
 * perform one simulation step
 * give an output depending on input
 */
class SISO
{
public:
    /*!
     * \brief Constructor
     */
    SISO();
    /*!
     * \brief simulate_step
     * perform one simulation step
     * give an output depending on input
     */
    virtual double Simulate_step(double input) = 0;
    /*!
     * \brief virtual desctructor
     */
    virtual ~SISO(){}
};

#endif // SISO_H
