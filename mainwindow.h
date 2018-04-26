#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "plotdelegate.h"
#include "arx.h"
#include "p.h"
#include "pid.h"
#include "config.h"
#include "regulationloop.h"
#include <string>
#include <sstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    explicit MainWindow(ARX *arx, PID *pid, Generator *generator, Config *conf, QWidget *parent=0);
    ~MainWindow();

private slots:
    void updateView();

    void on_startButton_clicked(bool checked);

    void on_stepButton_clicked(bool checked);

    void on_stopButton_clicked(bool checked);

    void on_restartButton_clicked(bool checked);
    void on_resetSetPoint_clicked(bool checked);

    void on_addStep_clicked();
    void on_addRectangle_clicked();
    void on_addSine_clicked();
    void on_addTriangle_clicked();
    void on_addNoise_clicked(bool checked);

    void on_horizontalSlider_valueChanged(int value);

    void on_changeRegulatorParametersButton_clicked(bool checked);

    void on_changeRegulatorButton_clicked(bool checked);

private:
    void PlotSP();

    Ui::MainWindow *ui;

    ARX *s_arx;
    Config *s_conf;
    Generator *s_generator;
    QTimer *timer;
    PID *s_pid;
    RegulationLoop *s_regLoop;


    PlotDelegate *s_plot1Delegate;
    PlotDelegate *s_plot2Delegate;
    PlotDelegate *s_plot3Delegate;


    QVector<double> s_SPVec = {};
    QVector<double> s_TimeVec = {};

    void updateViewStep();
    string doubleToString(double val);

    double currentOutput=0;
    int time=0;
    bool start=false;
    bool step = false;
    bool restarted = false;
};

#endif // MAINWINDOW_H
