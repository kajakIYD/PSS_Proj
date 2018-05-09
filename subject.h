#ifndef SUBJECT_H
#define SUBJECT_H
#include "observer.h"

class Observer;

class Subject
{
public:
    /*!
     * \brief Virtual destructor
     */
    virtual ~Subject (){}
    /*!
     * \brief Mehod that allows to register new observers
     * of type Observer*
     */
    bool RegisterObserver (Observer * observer);
    /*!
     * \brief Method that allows to unregister observers
     * of Observer* type
     */
    bool UnregisterObserver (Observer * observer);
    /*!
     * \brief Method that notifies the subjects (plots) and send
     * u on plot 2 and y at plot 1
     */
    void Notify (double u,  double y, double SP) const;
    void Notify (double u,  double y) const;
    void Notify (double y) const;
private:
    std::list<Observer * > s_Observers;
};

#endif // SUBJECT_H
