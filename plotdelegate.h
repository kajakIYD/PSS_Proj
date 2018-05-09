#ifndef PLOTDELEGATE_H
#define PLOTDELEGATE_H
#include "observer.h"
#include "ui_mainwindow.h"
#include <QVector>
#include "qcustomplot.h"

/*!
 * \brief simulate_step
 * perform one simulation step
 * double input -
 */
class PlotDelegate : public Observer
{
public:
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    PlotDelegate(Ui::MainWindow* ui, QMainWindow* mw);
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    virtual void Update(double u, double y, double SP);
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    virtual void Update(double u, double y);
    /*!
     * \brief simulate_step
     * perform one simulation step
     * double input -
     */
    virtual void Update(double y);

private:
    Ui::MainWindow * ui;
    double time=0;
    QVector<double> t={};
    QVector<double> y={};
    QVector<double> u={};
    QVector<double> SP={};
};

#endif // PLOTDELEGATE_H
